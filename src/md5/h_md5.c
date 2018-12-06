/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_md5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:06:12 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/12 13:06:14 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_md5.h"
#include "ft_printf.h"

static unsigned char g_pad_arr[64] = {
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static void	ft_ssl_md5_initialisation(t_md5_mssg *box, int flag_m)
{
	box->flag_m = flag_m;
	box->uint32[0] = 0;
	box->uint32[1] = 0;
	box->value_buf[0] = (unsigned long long)0x67452301;
	box->value_buf[1] = (unsigned long long)0xefcdab89;
	box->value_buf[2] = (unsigned long long)0x98badcfe;
	box->value_buf[3] = (unsigned long long)0x10325476;
}

static void	ft_ssl_md5_modifying(t_md5_mssg *box, ULLI len, uint8_t *data)
{
	ULLI	temp[16];
	int		mod64_c;

	mod64_c = (int)((box->uint32[0] >> 3) & 0x3F);
	if ((box->uint32[0] += ((ULLI)len << 3)) < ((ULLI)len << 3))
		box->uint32[1]++;
	box->uint32[1] += ((ULLI)len >> 29);
	while (len--)
	{
		box->input[mod64_c++] = *data++;
		if (mod64_c == 0x40)
		{
			ft_ssl_md5_tools(box, temp, 16);
			ft_ssl_md5_transformation(box->value_buf, temp);
			mod64_c = 0;
		}
	}
}

static void	ft_ssl_md5_build(t_md5_mssg *box)
{
	ULLI	in[16];
	int		mod64_c;
	ULLI	i;
	ULLI	j;
	ULLI	pad_len;

	in[14] = box->uint32[0];
	in[15] = box->uint32[1];
	i = 0;
	j = 0;
	mod64_c = (int)((box->uint32[0] >> 3) & 0x3F);
	pad_len = (mod64_c < 56) ? (56 - mod64_c) : (120 - mod64_c);
	ft_ssl_md5_modifying(box, pad_len, g_pad_arr);
	ft_ssl_md5_tools(box, in, 14);
	ft_ssl_md5_transformation(box->value_buf, &in[0]);
	while (i < 4)
	{
		box->dg_mssg[j] = (uint8_t)(box->value_buf[i] & 0xFF);
		box->dg_mssg[j + 1] = (uint8_t)((box->value_buf[i] >> 8) & 0xFF);
		box->dg_mssg[j + 2] = (uint8_t)((box->value_buf[i] >> 16) & 0xFF);
		box->dg_mssg[j + 3] = (uint8_t)((box->value_buf[i] >> 24) & 0xFF);
		i++;
		j += 4;
	}
}

static void	stream_r(uint8_t *str, ULLI len, int fd, t_md5_mssg *box)
{
	int		st;
	UCHAR	data[1024];

	ft_ssl_md5_modifying(box, len, str);
	while ((st = read(fd, &data[0], 1024)) != 0)
		ft_ssl_md5_modifying(box, st, data);
	ft_ssl_md5_build(box);
	if (box->flag_m & 0x2 && fd == 0)
		ft_printf("%s", str);
	ft_md5_print(box);
	if (!(box->flag_m & 0x8) || fd == 0 || (box->flag_m & 0x4))
		ft_printf("\n", data);
}

void		ft_ssl_md5(UCHAR *data, ULLI len, int fd, int flag_m)
{
	t_md5_mssg	box;

	ft_ssl_md5_initialisation(&box, flag_m);
	if (fd == STRING_MODE)
	{
		ft_ssl_md5_modifying(&box, len, data);
		ft_ssl_md5_build(&box);
		if (!(flag_m & 0x8) && !(flag_m & 0x4))
			ft_printf("MD5 (\"%s\") = ", data);
		ft_md5_print(&box);
		if (flag_m & 0x8 && !(flag_m & 0x4))
			ft_printf(" \"%s\"\n", data);
		else
			ft_printf("\n", data);
	}
	else
		stream_r(data, len, fd, &box);
}

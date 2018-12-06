/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:35:18 by lmatvien          #+#    #+#             */
/*   Updated: 2018/12/03 15:35:19 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha256.h"
#include "ft_printf.h"

static void	ft_sha256_print(UCHAR *block)
{
	int	i;

	i = 0;
	while (i < 32)
		ft_printf("%02x", block[i++]);
}

static void	stream_r(uint8_t *str, size_t len, int fd, t_sha_mssg *box)
{
	int		st;
	UCHAR	data[1024];
	UCHAR	block[32];

	sha256_h_modifying(box, str, len);
	while ((st = read(fd, &data[0], 1024)) != 0)
		sha256_h_modifying(box, data, st);
	sha256_h_build(box, &block[0]);
	if (box->flag_m & 0x2 && fd == 0)
		ft_printf("%s", str);
	ft_sha256_print(&block[0]);
	if (!(box->flag_m & 0x8) || fd == 0 || (box->flag_m & 0x4))
		ft_printf("\n", data);
}

void		ft_ssl_sha256(uint8_t *data, size_t len, int fd, int flag_m)
{
	t_sha_mssg		box;
	int				i;
	UCHAR			block[32];

	i = 0;
	sha256_v_init(&box.value_buff[0], &box.curr_byte,
		&box.mebit_len, &box.flag_m);
	if (fd == STRING_MODE)
	{
		sha256_h_modifying(&box, data, len);
		sha256_h_build(&box, &block[0]);
		if (!(flag_m & 0x8) && !(flag_m & 0x4))
			ft_printf("SHA256 (\"%s\") = ", data);
		ft_sha256_print(&block[0]);
		if (flag_m & 0x8 && !(flag_m & 0x4))
			ft_printf(" \"%s\"\n", data);
		else
			ft_printf("\n", data);
	}
	else
		stream_r(data, len, fd, &box);
}

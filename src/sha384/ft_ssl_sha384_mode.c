/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha384_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 20:38:28 by lmatvien          #+#    #+#             */
/*   Updated: 2018/12/04 20:38:31 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha384.h"
#include "ft_printf.h"

static void	ft_sha384_print(UCHAR *block)
{
	int	i;

	i = 0;
	while (i < 48)
		ft_printf("%02x", block[i++]);
	ft_printf("  -");
}

static void	stream_r(uint8_t *str, size_t len, int fd, t_sha384 *box)
{
	int		st;
	UCHAR	data[1024];
	UCHAR	block[64];

	sha384_h_modifying(box, str, len);
	while ((st = read(fd, &data[0], 1024)) != 0)
		sha384_h_modifying(box, str, len);
	sha384_h_build(box, &block[0]);
	if (box->flag_m & 0x2 && fd == 0)
		ft_printf("%s", str);
	ft_sha384_print(&block[0]);
	if (!(box->flag_m & 0x8) || fd == 0 || (box->flag_m & 0x4))
		ft_printf("\n", data);
}

void		ft_ssl_sha384(uint8_t *data, size_t len, int fd, int flag_m)
{
	t_sha384		box;
	int				i;
	UCHAR			block[64];

	i = 0;
	sha384_v_init(&box.value_buff[0], &box.curr_byte,
		&box.mebit_len, &box.flag_m);
	if (fd == STRING_MODE)
	{
		sha384_h_modifying(&box, data, len);
		sha384_h_build(&box, &block[0]);
		if (!(flag_m & 0x8) && !(flag_m & 0x4))
			ft_printf("SHA384 (\"%s\") = ", data);
		ft_sha384_print(&block[0]);
		if (flag_m & 0x8 && !(flag_m & 0x4))
			ft_printf(" \"%s\"\n", data);
		else
			ft_printf("\n", data);
	}
	else
		stream_r(data, len, fd, &box);
}

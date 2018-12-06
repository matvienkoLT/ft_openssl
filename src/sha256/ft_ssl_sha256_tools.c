/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:53:58 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/23 10:53:59 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha256.h"

#define POINT (24 - (i << 3))

static unsigned char g_pad_arr[64] = {
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void	padding_to_block(t_sha_mssg *box, size_t len)
{
	int		mod64_c;
	uint8_t	*dt;

	mod64_c = box->curr_byte;
	dt = &(g_pad_arr[0]);
	while (len--)
		box->data[mod64_c++] = *dt++;
}

void	reverse_sha256_byte(uint8_t *data, uint32_t *var)
{
	int i;

	i = 0;
	while (i < 4)
	{
		data[i] = (var[0] >> (24 - (i << 3))) & 0xff;
		data[i + 4] = (var[1] >> POINT) & 0xff;
		data[i + 8] = (var[2] >> POINT) & 0xff;
		data[i + 12] = (var[3] >> POINT) & 0xff;
		data[i + 16] = (var[4] >> POINT) & 0xff;
		data[i + 20] = (var[5] >> POINT) & 0xff;
		data[i + 24] = (var[6] >> POINT) & 0xff;
		data[i + 28] = (var[7] >> POINT) & 0xff;
		i++;
	}
}

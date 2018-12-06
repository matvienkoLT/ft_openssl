/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha224.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:58:55 by lmatvien          #+#    #+#             */
/*   Updated: 2018/12/03 15:58:56 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha224.h"
#include "ft_printf.h"

#define CURR_B box->curr_byte
#define RIGHT_ROTATE(x, y) ((x >> y) | (x << (32 - y)))
#define S_0(v) (RIGHT_ROTATE(v, 7) ^ RIGHT_ROTATE(v, 18) ^ (v >> 3))
#define S_1(v) (RIGHT_ROTATE(v, 17) ^ RIGHT_ROTATE(v, 19) ^ (v >> 10))

static void	sha224_tools(t_sha224 *box, uint32_t *temp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		temp[i] = (box->data[j] << 24 |
			(box->data[j + 1] << 16) |
			(box->data[j + 2] << 8) |
			(box->data[j + 3]));
		i++;
		j += 4;
	}
	while (i < 64)
	{
		temp[i] = temp[i - 16] + S_0(temp[i - 15]) +
			temp[i - 7] + S_1(temp[i - 2]);
		i++;
	}
}

void		sha224_v_init(uint32_t *var, int *curr_b, uint64_t *wbite, int *fl)
{
	*fl = 0;
	*curr_b = (unsigned long long)0;
	*wbite = (unsigned long long)0;
	var[0] = (unsigned long long)0xC1059ED8;
	var[1] = (unsigned long long)0x367CD507;
	var[2] = (unsigned long long)0x3070DD17;
	var[3] = (unsigned long long)0xF70E5939;
	var[4] = (unsigned long long)0xFFC00B31;
	var[5] = (unsigned long long)0x68581511;
	var[6] = (unsigned long long)0x64F98FA7;
	var[7] = (unsigned long long)0xBEFA4FA4;
}

void		sha224_h_modifying(t_sha224 *box, uint8_t *data, size_t len)
{
	int			*mod64_c;
	uint32_t	word[64];

	mod64_c = &box->curr_byte;
	while (len--)
	{
		box->data[(*mod64_c)++] = *data++;
		if (*mod64_c == 0x40)
		{
			sha224_tools(box, &word[0]);
			ft_ssl_sha224_tranforrm(box, &word[0]);
			box->mebit_len += (uint32_t)512;
			*mod64_c = 0;
		}
	}
}

void		sha224_h_build(t_sha224 *box, uint8_t *data)
{
	uint32_t pad_len;
	uint32_t word[64];

	pad_len = (CURR_B < 56) ? (56 - CURR_B) : (120 - CURR_B);
	padding_to_block_224(box, pad_len);
	box->mebit_len += (CURR_B * 8);
	box->data[63] = box->mebit_len;
	box->data[62] = box->mebit_len >> 8;
	box->data[61] = box->mebit_len >> 16;
	box->data[60] = box->mebit_len >> 24;
	box->data[59] = box->mebit_len >> 32;
	box->data[58] = box->mebit_len >> 40;
	box->data[57] = box->mebit_len >> 48;
	box->data[56] = box->mebit_len >> 56;
	sha224_tools(box, &word[0]);
	ft_ssl_sha224_tranforrm(box, &word[0]);
	reverse_sha224_byte(data, &box->value_buff[0]);
}

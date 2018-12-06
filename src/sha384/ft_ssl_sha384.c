/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha384.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 20:41:18 by lmatvien          #+#    #+#             */
/*   Updated: 2018/12/04 20:41:20 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha384.h"

#define CURR_B box->curr_byte
#define RIGHT_ROTATE(x, y) ((x >> y) | (x << (64 - y)))
#define S_0(v) (RIGHT_ROTATE(v, 1) ^ RIGHT_ROTATE(v, 8) ^ (v >> 7))
#define S_1(v) (RIGHT_ROTATE(v, 19) ^ RIGHT_ROTATE(v, 61) ^ (v >> 6))

static void	sha384_tools(t_sha384 *box, uint64_t *temp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		temp[i] = ((uint64_t)box->data[j] << 56 |
			((uint64_t)box->data[j + 1] << 48) |
			((uint64_t)box->data[j + 2] << 40) |
			((uint64_t)box->data[j + 3] << 32) |
			((uint64_t)box->data[j + 4] << 24) |
			((uint64_t)box->data[j + 5] << 16) |
			((uint64_t)box->data[j + 6] << 8) | ((uint64_t)box->data[j + 7]));
		i++;
		j += 8;
	}
	while (i < 80)
	{
		temp[i] = temp[i - 16] + S_0(temp[i - 15]) +
			temp[i - 7] + S_1(temp[i - 2]);
		i++;
	}
}

void		sha384_v_init(uint64_t *var, int *curr_b, uint64_t *wbite, int *fl)
{
	*fl = 0;
	*curr_b = 0ULL;
	*wbite = 0ULL;
	var[0] = 0xcbbb9d5dc1059ed8ULL;
	var[1] = 0x629a292a367cd507ULL;
	var[2] = 0x9159015a3070dd17ULL;
	var[3] = 0x152fecd8f70e5939ULL;
	var[4] = 0x67332667ffc00b31ULL;
	var[5] = 0x8eb44a8768581511ULL;
	var[6] = 0xdb0c2e0d64f98fa7ULL;
	var[7] = 0x47b5481dbefa4fa4ULL;
}

void		sha384_h_modifying(t_sha384 *box, uint8_t *data, size_t len)
{
	int			*mod64_c;
	uint64_t	word[80];

	mod64_c = &box->curr_byte;
	while (len--)
	{
		box->data[(*mod64_c)++] = *data++;
		if (*mod64_c == 0x80)
		{
			sha384_tools(box, &word[0]);
			ft_ssl_sha384_tranforrm(box, &word[0]);
			box->mebit_len += (uint64_t)1024;
			*mod64_c = 0;
		}
	}
}

void		sha384_h_build(t_sha384 *box, uint8_t *data)
{
	uint64_t	pad_len;
	uint64_t	word[80];
	int			u;
	int			i;

	u = 0;
	i = 0;
	pad_len = (CURR_B < 112) ? (112 - CURR_B) : (240 - CURR_B);
	padding_to_block_384(box, pad_len);
	box->mebit_len += (CURR_B * 8);
	box->data[127] = box->mebit_len;
	box->data[126] = box->mebit_len >> 8;
	box->data[125] = box->mebit_len >> 16;
	box->data[124] = box->mebit_len >> 24;
	box->data[123] = box->mebit_len >> 32;
	box->data[122] = box->mebit_len >> 40;
	box->data[121] = box->mebit_len >> 48;
	box->data[120] = box->mebit_len >> 56;
	sha384_tools(box, &word[0]);
	ft_ssl_sha384_tranforrm(box, &word[0]);
	while (u < 64)
	{
		reverse_sha384_byte(&data[u], box->value_buff[i++]);
		u += 8;
	}
}

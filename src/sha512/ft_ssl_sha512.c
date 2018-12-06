/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha512.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:39:05 by lmatvien          #+#    #+#             */
/*   Updated: 2018/12/03 16:39:06 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha512.h"

#define CURR_B box->curr_byte
#define RIGHT_ROTATE(x, y) ((x >> y) | (x << (64 - y)))
#define S_0(v) (RIGHT_ROTATE(v, 1) ^ RIGHT_ROTATE(v, 8) ^ (v >> 7))
#define S_1(v) (RIGHT_ROTATE(v, 19) ^ RIGHT_ROTATE(v, 61) ^ (v >> 6))

static void	sha512_tools(t_sha512 *box, uint64_t *temp)
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

void		sha512_v_init(uint64_t *var, int *curr_b, uint64_t *wbite, int *fl)
{
	*fl = 0;
	*curr_b = 0ULL;
	*wbite = 0ULL;
	var[0] = 0x6a09e667f3bcc908ULL;
	var[1] = 0xbb67ae8584caa73bULL;
	var[2] = 0x3c6ef372fe94f82bULL;
	var[3] = 0xa54ff53a5f1d36f1ULL;
	var[4] = 0x510e527fade682d1ULL;
	var[5] = 0x9b05688c2b3e6c1fULL;
	var[6] = 0x1f83d9abfb41bd6bULL;
	var[7] = 0x5be0cd19137e2179ULL;
}

void		sha512_h_modifying(t_sha512 *box, uint8_t *data, size_t len)
{
	int			*mod64_c;
	uint64_t	word[80];

	mod64_c = &box->curr_byte;
	while (len--)
	{
		box->data[(*mod64_c)++] = *data++;
		if (*mod64_c == 0x80)
		{
			sha512_tools(box, &word[0]);
			ft_ssl_sha512_tranforrm(box, &word[0]);
			box->mebit_len += (uint64_t)1024;
			*mod64_c = 0;
		}
	}
}

void		sha512_h_build(t_sha512 *box, uint8_t *data)
{
	uint64_t	pad_len;
	uint64_t	word[80];
	int			u;
	int			i;

	u = 0;
	i = 0;
	pad_len = (CURR_B < 112) ? (112 - CURR_B) : (240 - CURR_B);
	padding_to_block_512(box, pad_len);
	box->mebit_len += (CURR_B * 8);
	box->data[127] = box->mebit_len;
	box->data[126] = box->mebit_len >> 8;
	box->data[125] = box->mebit_len >> 16;
	box->data[124] = box->mebit_len >> 24;
	box->data[123] = box->mebit_len >> 32;
	box->data[122] = box->mebit_len >> 40;
	box->data[121] = box->mebit_len >> 48;
	box->data[120] = box->mebit_len >> 56;
	sha512_tools(box, &word[0]);
	ft_ssl_sha512_tranforrm(box, &word[0]);
	while (u < 64)
	{
		reverse_sha512_byte(&data[u], box->value_buff[i++]);
		u += 8;
	}
}

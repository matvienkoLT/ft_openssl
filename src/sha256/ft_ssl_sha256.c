/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:00:02 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/21 18:00:03 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha256.h"
#include "ft_printf.h"

#define CURR_B box->curr_byte
#define RIGHT_ROTATE(x, y) ((x >> y) | (x << (32 - y)))
#define S_0(v) (RIGHT_ROTATE(v, 7) ^ RIGHT_ROTATE(v, 18) ^ (v >> 3))
#define S_1(v) (RIGHT_ROTATE(v, 17) ^ RIGHT_ROTATE(v, 19) ^ (v >> 10))

static void	sha256_tools(t_sha_mssg *box, uint32_t *temp)
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

void		sha256_v_init(uint32_t *var, int *curr_b, uint64_t *wbite, int *fl)
{
	*fl = 0;
	*curr_b = (unsigned long long)0;
	*wbite = (unsigned long long)0;
	var[0] = (unsigned long long)0x6A09E667;
	var[1] = (unsigned long long)0xBB67AE85;
	var[2] = (unsigned long long)0x3C6EF372;
	var[3] = (unsigned long long)0xA54FF53A;
	var[4] = (unsigned long long)0x510E527F;
	var[5] = (unsigned long long)0x9B05688C;
	var[6] = (unsigned long long)0x1F83D9AB;
	var[7] = (unsigned long long)0x5BE0CD19;
}

void		sha256_h_modifying(t_sha_mssg *box, uint8_t *data, size_t len)
{
	int			*mod64_c;
	uint32_t	word[64];

	mod64_c = &box->curr_byte;
	while (len--)
	{
		box->data[(*mod64_c)++] = *data++;
		if (*mod64_c == 0x40)
		{
			sha256_tools(box, &word[0]);
			ft_ssl_sha256_tranforrm(box, &word[0]);
			box->mebit_len += (uint32_t)512;
			*mod64_c = 0;
		}
	}
}

void		sha256_h_build(t_sha_mssg *box, uint8_t *data)
{
	uint32_t pad_len;
	uint32_t word[64];

	pad_len = (CURR_B < 56) ? (56 - CURR_B) : (120 - CURR_B);
	padding_to_block(box, pad_len);
	box->mebit_len += (CURR_B * 8);
	box->data[63] = box->mebit_len;
	box->data[62] = box->mebit_len >> 8;
	box->data[61] = box->mebit_len >> 16;
	box->data[60] = box->mebit_len >> 24;
	box->data[59] = box->mebit_len >> 32;
	box->data[58] = box->mebit_len >> 40;
	box->data[57] = box->mebit_len >> 48;
	box->data[56] = box->mebit_len >> 56;
	sha256_tools(box, &word[0]);
	ft_ssl_sha256_tranforrm(box, &word[0]);
	reverse_sha256_byte(data, &box->value_buff[0]);
}

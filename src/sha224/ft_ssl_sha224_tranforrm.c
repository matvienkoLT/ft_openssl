/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha224_tranforrm.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:58:15 by lmatvien          #+#    #+#             */
/*   Updated: 2018/12/03 15:58:16 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha224.h"

#define R_ROTATE(x, y) ((x >> y) | (x << (32 - y)))
#define SIGMA_0(v) (R_ROTATE(v, 2) ^ R_ROTATE(v, 13) ^ R_ROTATE(v, 22))
#define SIGMA_1(v) (R_ROTATE(v, 6) ^ R_ROTATE(v, 11) ^ R_ROTATE(v, 25))
#define MA(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define CH(x, y, z) ((x & y) ^ (~x & z))

static const uint32_t g_cubic_r[64] = {
	0x428a2f98, 0x71374491,
	0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe,
	0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d,
	0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb,
	0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08,
	0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb,
	0xbef9a3f7, 0xc67178f2};

static void	value_buff_intitialisation(t_sha224 *box, uint32_t *value_buff)
{
	value_buff[0] = box->value_buff[0];
	value_buff[1] = box->value_buff[1];
	value_buff[2] = box->value_buff[2];
	value_buff[3] = box->value_buff[3];
	value_buff[4] = box->value_buff[4];
	value_buff[5] = box->value_buff[5];
	value_buff[6] = box->value_buff[6];
	value_buff[7] = box->value_buff[7];
}

static void	reassignment_v(uint32_t *v_buff, uint32_t t1, uint32_t t2)
{
	v_buff[7] = v_buff[6];
	v_buff[6] = v_buff[5];
	v_buff[5] = v_buff[4];
	v_buff[4] = v_buff[3] + t1;
	v_buff[3] = v_buff[2];
	v_buff[2] = v_buff[1];
	v_buff[1] = v_buff[0];
	v_buff[0] = t2 + t1;
}

void		ft_ssl_sha224_tranforrm(t_sha224 *box, uint32_t *temp)
{
	uint32_t	v_buff[8];
	uint32_t	t1;
	uint32_t	t2;
	int			i;

	i = 0;
	value_buff_intitialisation(box, &v_buff[0]);
	while (i < 64)
	{
		t2 = SIGMA_0(v_buff[0]) + MA(v_buff[0], v_buff[1], v_buff[2]);
		t1 = v_buff[7] + SIGMA_1(v_buff[4]) +
			CH(v_buff[4], v_buff[5], v_buff[6])
			+ g_cubic_r[i] + temp[i];
		reassignment_v(&v_buff[0], t1, t2);
		i++;
	}
	box->value_buff[0] += v_buff[0];
	box->value_buff[1] += v_buff[1];
	box->value_buff[2] += v_buff[2];
	box->value_buff[3] += v_buff[3];
	box->value_buff[4] += v_buff[4];
	box->value_buff[5] += v_buff[5];
	box->value_buff[6] += v_buff[6];
}

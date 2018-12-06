/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_md5_transforrm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:12:26 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/12 17:12:27 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_md5.h"

/*
** Precomputed constant table
*/

static const uint32_t g_table[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

/*
** Defined the per-round shift amounts
*/
static const uint32_t g_s[] = {
	7, 12, 17, 22, 7,
	12, 17, 22, 7, 12,
	17, 22, 7, 12, 17,
	22, 5, 9, 14, 20,
	5, 9, 14, 20, 5,
	9, 14, 20, 5, 9,
	14, 20, 4, 11, 16,
	23, 4, 11, 16, 23,
	4, 11, 16, 23, 4,
	11, 16, 23, 6, 10,
	15, 21, 6, 10, 15,
	21, 6, 10, 15, 21,
	6, 10, 15, 21};
/*
** Leftrotate function definition
*/
#define LEFT_ROTATE(x, y) ((x << y) | (x >> (32 - y)))
#define F(b, c, d) ((b & c) | ((~b) & d))
#define G(b, c, d) ((b & d) | (c & (~d)))
#define H(b, c, d) (b ^ c ^ d)
#define I(b, c, d) (c ^ (b | (~d)))

#define FIR(a, b, c, d, p, s, t) a += F(b, c, d) + p + t
#define FRR(a, b, s) a = LEFT_ROTATE(a, s); a += b
#define F_R(a, b, c, d, p, s, t) FIR(a, b, c, d, p, s, t); FRR(a, b, s)

#define GIR(a, b, c, d, p, s, t) a += G(b, c, d) + p + t
#define GRR(a, b, s) a = LEFT_ROTATE(a, s); a += b
#define G_R(a, b, c, d, p, s, t) GIR(a, b, c, d, p, s, t); GRR(a, b, s)

#define HIR(a, b, c, d, p, s, t) a += H(b, c, d) + p + t
#define HRR(a, b, s) a = LEFT_ROTATE(a, s); a += b
#define H_R(a, b, c, d, p, s, t) HIR(a, b, c, d, p, s, t); HRR(a, b, s)

#define IIR(a, b, c, d, p, s, t) a += I(b, c, d) + p + t
#define IRR(a, b, s) a = LEFT_ROTATE(a, s); a += b
#define I_R(a, b, c, d, p, s, t) IIR(a, b, c, d, p, s, t); IRR(a, b, s)

static void	md5_round_one(uint32_t *p, uint32_t *hash)
{
	F_R(p[0], p[1], p[2], p[3], hash[0], 0x7, 0xd76aa478);
	F_R(p[3], p[0], p[1], p[2], hash[1], 0xC, 0xE8C7B756);
	F_R(p[2], p[3], p[0], p[1], hash[2], 0x11, 0x242070DB);
	F_R(p[1], p[2], p[3], p[0], hash[3], 0x16, 0xC1BDCEEE);
	F_R(p[0], p[1], p[2], p[3], hash[4], 0x7, 0xF57C0FAF);
	F_R(p[3], p[0], p[1], p[2], hash[5], 0xC, 0x4787C62A);
	F_R(p[2], p[3], p[0], p[1], hash[6], 0x11, 0xa8304613);
	F_R(p[1], p[2], p[3], p[0], hash[7], 0x16, 0xFD469501);
	F_R(p[0], p[1], p[2], p[3], hash[8], 0x7, 0x698098D8);
	F_R(p[3], p[0], p[1], p[2], hash[9], 0xC, 0x8B44F7AF);
	F_R(p[2], p[3], p[0], p[1], hash[10], 0x11, 0xFFFF5BB1);
	F_R(p[1], p[2], p[3], p[0], hash[11], 0x16, 0x895CD7BE);
	F_R(p[0], p[1], p[2], p[3], hash[12], 0x7, 0x6B901122);
	F_R(p[3], p[0], p[1], p[2], hash[13], 0xC, 0xFD987193);
	F_R(p[2], p[3], p[0], p[1], hash[14], 0x11, 0xA679438E);
	F_R(p[1], p[2], p[3], p[0], hash[15], 0x16, 0x49B40821);
}

static void	md5_round_two(uint32_t *p, uint32_t *hash)
{
	G_R(p[0], p[1], p[2], p[3], hash[1], 0x5, 0xF61E2562);
	G_R(p[3], p[0], p[1], p[2], hash[6], 0x9, 0xc040b340);
	G_R(p[2], p[3], p[0], p[1], hash[11], 0xE, 0x265e5a51);
	G_R(p[1], p[2], p[3], p[0], hash[0], 0x14, 0xe9b6c7aa);
	G_R(p[0], p[1], p[2], p[3], hash[5], 0x5, 0xd62f105d);
	G_R(p[3], p[0], p[1], p[2], hash[10], 0x9, 0x2441453);
	G_R(p[2], p[3], p[0], p[1], hash[15], 0xE, 0xd8a1e681);
	G_R(p[1], p[2], p[3], p[0], hash[4], 0x14, 0xe7d3fbc8);
	G_R(p[0], p[1], p[2], p[3], hash[9], 0x5, 0x21e1cde6);
	G_R(p[3], p[0], p[1], p[2], hash[14], 0x9, 0xc33707d6);
	G_R(p[2], p[3], p[0], p[1], hash[3], 0xE, 0xf4d50d87);
	G_R(p[1], p[2], p[3], p[0], hash[8], 0x14, 0x455a14ed);
	G_R(p[0], p[1], p[2], p[3], hash[13], 0x5, 0xa9e3e905);
	G_R(p[3], p[0], p[1], p[2], hash[2], 0x9, 0xfcefa3f8);
	G_R(p[2], p[3], p[0], p[1], hash[7], 0xE, 0x676f02d9);
	G_R(p[1], p[2], p[3], p[0], hash[12], 0x14, 0x8d2a4c8a);
}

static void	md5_round_three(uint32_t *p, uint32_t *hash)
{
	H_R(p[0], p[1], p[2], p[3], hash[5], 0x4, 0xfffa3942);
	H_R(p[3], p[0], p[1], p[2], hash[8], 0xB, 0x8771f681);
	H_R(p[2], p[3], p[0], p[1], hash[11], 0x10, 0x6d9d6122);
	H_R(p[1], p[2], p[3], p[0], hash[14], 0x17, 0xfde5380c);
	H_R(p[0], p[1], p[2], p[3], hash[1], 0x4, 0xa4beea44);
	H_R(p[3], p[0], p[1], p[2], hash[4], 0xB, 0x4bdecfa9);
	H_R(p[2], p[3], p[0], p[1], hash[7], 0x10, 0xf6bb4b60);
	H_R(p[1], p[2], p[3], p[0], hash[10], 0x17, 0xbebfbc70);
	H_R(p[0], p[1], p[2], p[3], hash[13], 0x4, 0x289b7ec6);
	H_R(p[3], p[0], p[1], p[2], hash[0], 0xB, 0xeaa127fa);
	H_R(p[2], p[3], p[0], p[1], hash[3], 0x10, 0xd4ef3085);
	H_R(p[1], p[2], p[3], p[0], hash[6], 0x17, 0x4881d05);
	H_R(p[0], p[1], p[2], p[3], hash[9], 0x4, 0xd9d4d039);
	H_R(p[3], p[0], p[1], p[2], hash[12], 0xB, 0xe6db99e5);
	H_R(p[2], p[3], p[0], p[1], hash[15], 0x10, 0x1fa27cf8);
	H_R(p[1], p[2], p[3], p[0], hash[2], 0x17, 0xc4ac5665);
}

static void	md5_round_four(uint32_t *p, uint32_t *hash)
{
	I_R(p[0], p[1], p[2], p[3], hash[0], 0x6, 0xf4292244);
	I_R(p[3], p[0], p[1], p[2], hash[7], 0xA, 0x432aff97);
	I_R(p[2], p[3], p[0], p[1], hash[14], 0xF, 0xab9423a7);
	I_R(p[1], p[2], p[3], p[0], hash[5], 0x15, 0xfc93a039);
	I_R(p[0], p[1], p[2], p[3], hash[12], 0x6, 0x655b59c3);
	I_R(p[3], p[0], p[1], p[2], hash[3], 0xA, 0x8f0ccc92);
	I_R(p[2], p[3], p[0], p[1], hash[10], 0xF, 0xffeff47d);
	I_R(p[1], p[2], p[3], p[0], hash[1], 0x15, 0x85845dd1);
	I_R(p[0], p[1], p[2], p[3], hash[8], 0x6, 0x6fa87e4f);
	I_R(p[3], p[0], p[1], p[2], hash[15], 0xA, 0xfe2ce6e0);
	I_R(p[2], p[3], p[0], p[1], hash[6], 0xF, 0xa3014314);
	I_R(p[1], p[2], p[3], p[0], hash[13], 0x15, 0x4e0811a1);
	I_R(p[0], p[1], p[2], p[3], hash[4], 0x6, 0xf7537e82);
	I_R(p[3], p[0], p[1], p[2], hash[11], 0xA, 0xbd3af235);
	I_R(p[2], p[3], p[0], p[1], hash[2], 0xF, 0x2ad7d2bb);
	I_R(p[1], p[2], p[3], p[0], hash[9], 0x15, 0xeb86d391);
}

void		ft_ssl_md5_transformation(uint32_t *val_buf, uint32_t *hash)
{
	uint32_t p[4];

	p[0] = val_buf[0];
	p[1] = val_buf[1];
	p[2] = val_buf[2];
	p[3] = val_buf[3];
	md5_round_one(p, hash);
	md5_round_two(p, hash);
	md5_round_three(p, hash);
	md5_round_four(p, hash);
	val_buf[0] += p[0];
	val_buf[1] += p[1];
	val_buf[2] += p[2];
	val_buf[3] += p[3];
}

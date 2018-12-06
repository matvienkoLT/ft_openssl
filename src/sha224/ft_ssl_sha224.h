/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha224.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:59:23 by lmatvien          #+#    #+#             */
/*   Updated: 2018/12/03 15:59:24 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA224_H
# define FT_SSL_SHA224_H

# include <stdint.h>
# include "libft.h"

# define UCHAR unsigned char
# define STRING_MODE -2

typedef struct	s_sha224
{
	uint8_t		data[64];
	uint32_t	value_buff[8];
	uint64_t	mebit_len;
	int			curr_byte;
	uint8_t		input_message[32];
	int			flag_m;
}				t_sha224;

void			ft_ssl_sha224(uint8_t *data, size_t len, int fd, int flag_m);
void			ft_ssl_sha224_tranforrm(t_sha224 *box, uint32_t *temp);
void			padding_to_block_224(t_sha224 *box, size_t len);
void			reverse_sha224_byte(uint8_t *data, uint32_t *var);
void			sha224_v_init(uint32_t *var, int *c_b, uint64_t *wb, int *fl);
void			sha224_h_build(t_sha224 *box, uint8_t *data);
void			sha224_h_modifying(t_sha224 *box, uint8_t *data, size_t len);
#endif

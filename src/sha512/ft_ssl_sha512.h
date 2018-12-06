/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha512.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:39:11 by lmatvien          #+#    #+#             */
/*   Updated: 2018/12/03 16:39:12 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA512_H
# define FT_SSL_SHA512_H

# include <stdint.h>
# include "libft.h"

# define UCHAR unsigned char
# define STRING_MODE -2

typedef struct	s_sha512
{
	uint8_t		data[128];
	uint64_t	value_buff[8];
	uint64_t	mebit_len;
	int			curr_byte;
	uint8_t		input_message[64];
	int			flag_m;
}				t_sha512;

void			ft_ssl_sha512(uint8_t *data, size_t len, int fd, int flag_m);
void			ft_ssl_sha512_tranforrm(t_sha512 *box, uint64_t *temp);
void			padding_to_block_512(t_sha512 *box, size_t len);
void			reverse_sha512_byte(uint8_t *data, uint64_t var);
void			sha512_v_init(uint64_t *var, int *c_b, uint64_t *wb, int *fl);
void			sha512_h_build(t_sha512 *box, uint8_t *data);
void			sha512_h_modifying(t_sha512 *box, uint8_t *data, size_t len);
#endif

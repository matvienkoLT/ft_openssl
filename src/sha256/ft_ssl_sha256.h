/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:59:52 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/21 17:59:54 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA256_H
# define FT_SSL_SHA256_H

# include <stdint.h>
# include "libft.h"

# define UCHAR unsigned char
# define STRING_MODE -2

typedef struct	s_sha_mssg
{
	uint8_t		data[64];
	uint32_t	value_buff[8];
	uint64_t	mebit_len;
	int			curr_byte;
	uint8_t		input_message[32];
	int			flag_m;
}				t_sha_mssg;

void			ft_ssl_sha256(uint8_t *data, size_t len, int fd, int flag_m);
void			ft_ssl_sha256_tranforrm(t_sha_mssg *box, uint32_t *temp);
void			padding_to_block(t_sha_mssg *box, size_t len);
void			reverse_sha256_byte(uint8_t *data, uint32_t *var);
void			sha256_v_init(uint32_t *var, int *c_b, uint64_t *wb, int *fl);
void			sha256_h_build(t_sha_mssg *box, uint8_t *data);
void			sha256_h_modifying(t_sha_mssg *box, uint8_t *data, size_t len);
#endif

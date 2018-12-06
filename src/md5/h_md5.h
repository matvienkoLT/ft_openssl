/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_md5.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:06:51 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/12 13:06:53 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MD5_H
# define H_MD5_H

# include <stdint.h>
# include "libft.h"

# define UCHAR unsigned char
# define ULLI uint32_t
# define STRING_MODE -2

typedef struct	s_md5_mssg
{
	uint32_t	uint32[2];
	ULLI		value_buf[4];
	UCHAR		input[64];
	UCHAR		dg_mssg[16];
	int			flag_m;
}				t_md5_mssg;

void			ft_ssl_md5(UCHAR *data, ULLI len, int fd, int flag_m);
void			ft_ssl_md5_transformation(uint32_t *val_buf, uint32_t *hash);
void			ft_ssl_md5_tools(t_md5_mssg *box, ULLI *temp, ULLI to_value);
void			ft_md5_print(t_md5_mssg *box);

#endif

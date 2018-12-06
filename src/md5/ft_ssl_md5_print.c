/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:42:28 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/20 18:42:28 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_md5.h"
#include "ft_printf.h"

void	ft_ssl_md5_tools(t_md5_mssg *box, ULLI *temp, ULLI to_value)
{
	ULLI i;
	ULLI j;

	i = 0;
	j = 0;
	while (i < to_value)
	{
		temp[i] = (((ULLI)box->input[j + 3]) << 24) |
					(((ULLI)box->input[j + 2]) << 16) |
					(((ULLI)box->input[j + 1]) << 8) |
					((ULLI)box->input[j]);
		i++;
		j += 4;
	}
}

void	ft_md5_print(t_md5_mssg *box)
{
	int i;

	i = 0;
	while (i < 16)
	{
		ft_printf("%02x", box->dg_mssg[i]);
		i++;
	}
}

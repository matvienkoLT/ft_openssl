/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_del_newline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:01:07 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/07 17:01:08 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_str_del_newline(char *dest)
{
	char	*str;

	str = dest;
	if (str != NULL)
	{
		while (*str != '\0')
		{
			*str == 0xA ? *str = 0x0 : *str;
			(str)++;
		}
	}
}

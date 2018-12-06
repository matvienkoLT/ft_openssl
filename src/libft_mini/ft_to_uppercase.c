/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_uppercase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:40:44 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/28 19:40:45 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_to_upper_c(char *data)
{
	char	*str;

	if (data)
	{
		str = data;
		while (*str)
		{
			if (*str >= 0x61 && *str <= 0x7a)
				*str -= 0x20;
			str++;
		}
	}
	return (data);
}

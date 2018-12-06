/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_lowercase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:21:53 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/29 19:21:54 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_to_lowercase(char *data)
{
	char *str;

	if (data)
	{
		str = data;
		while (*str)
		{
			if (*str >= 0x41 && *str <= 0x5a)
				*str += 0x20;
			str++;
		}
	}
	return (data);
}

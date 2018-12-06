/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_hash_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:41:13 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/01 16:41:14 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_header.h"

static int	check_belonging_to(char *data, int *h_mode)
{
	int		index;

	index = 0;
	while (index < CMSSG_ELMT)
	{
		if (ft_strcmp(g_hash_mode[index], (char *)data) == 0)
		{
			*h_mode = index;
			return (FLG_DETECT);
		}
		index++;
	}
	return (FLG_NFND);
}

int			detect_type_hash_argc(char *data, int *h_mode)
{
	if (check_belonging_to(&data[0], h_mode) == FLG_DETECT)
		return (EXIT_SUCCESS);
	else
		display_usage(data);
	return (EXIT_FAILURE);
}

int			detect_type_hash(int *h_mode)
{
	int		st;
	char	data[30];

	ft_printf("FT_SSL> ");
	while ((st = read(0, &data[0], 30)) != 0)
	{
		ft_str_del_newline(data);
		if (check_belonging_to(&data[0], h_mode) == FLG_DETECT)
			return (EXIT_SUCCESS);
		else
		{
			display_usage(data);
			ft_printf("\nFT_SSL> ");
		}
		ft_memset(&data[0], 0, 30);
	}
	return (EXIT_FAILURE);
}

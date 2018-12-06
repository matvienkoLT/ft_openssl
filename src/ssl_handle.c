/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:30:44 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/06 18:30:45 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_header.h"

static void	mode_printer(char **data, int c_qntty)
{
	int	index;
	int	c_printed_element;

	index = 0;
	c_printed_element = 0;
	while (index < c_qntty)
	{
		ft_printf("%10s", data[index]);
		index++;
		if (++c_printed_element > 3)
		{
			ft_printf("\n");
			c_printed_element = 0;
		}
	}
	ft_printf("\n");
}

int			display_usage_flag(char *data)
{
	ft_printf("unknown option '%s'\noptions are\n", data);
	ft_printf("-p          %s\n-q          %s\n", MESSAGE_P, MESSAGE_Q);
	ft_printf("-r          %s\n-s          %s\n", MESSAGE_R, MESSAGE_S);
	return (EXIT_FAILURE);
}

void		display_usage(char *data)
{
	ft_printf("\nft_ssl:Error: '%s' is an invalid command.\n", data);
	ft_printf("\nStandard commands\n");
	if (CSTCMMND_ELMT > 0)
		mode_printer(&g_stdrt_comm[0], CSTCMMND_ELMT);
	ft_printf("\nMessage Digest commands\n");
	if (CMSSG_ELMT > 0)
		mode_printer(&g_hash_mode[0], CMSSG_ELMT);
	ft_printf("\nCipher commands\n");
	if (CMSSD_ELMN > 0)
		mode_printer(&g_cl_comm[0], CMSSD_ELMN);
}

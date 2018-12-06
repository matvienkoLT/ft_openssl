/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_flags_mod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:20:15 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/08 18:20:16 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_header.h"

#define I opt->curr_argc_index

static int	cmp_flags(char *argv, t_prms *opt)
{
	if (!ft_strcmp(argv, "-p"))
		opt->flag_mod |= FLAG_P;
	else if (!ft_strcmp(argv, "-q"))
		opt->flag_mod |= FLAG_Q;
	else if (!ft_strcmp(argv, "-r"))
		opt->flag_mod |= FLAG_R;
	else if (!ft_strcmp(argv, "-s"))
	{
		opt->flag_mod |= FLAG_S;
		return (STRING_MODE);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			type_flag(char **argv, int argc, t_prms *opt)
{
	int status;

	status = 1;
	I = 2;
	while (I < argc)
	{
		if (argv[I][0] == '-')
		{
			if ((status = cmp_flags(argv[I], opt)) == EXIT_FAILURE)
				return (display_usage_flag(argv[I]));
			else if (status == STRING_MODE)
			{
				I++;
				break ;
			}
		}
		else
			break ;
		I++;
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:28:06 by lmatvien          #+#    #+#             */
/*   Updated: 2018/10/30 17:28:07 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_header.h"

int	main(int argc, char **argv)
{
	t_prms	options;

	ft_memset(&options, 0, sizeof(int) * 4);
	options.hash_mod = -1;
	if (argc == 1)
	{
		if (stdin_reader(&options.hash_mod) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (flag_effect(argc, argv, &options) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (argc >= 2)
	{
		if (detect_type_hash_argc(argv[1], &options.hash_mod) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (type_flag(argv, argc, &options) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (flag_effect(argc, argv, &options) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

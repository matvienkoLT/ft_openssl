/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_flag_effect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:44:06 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/29 18:44:07 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_header.h"

#define I opt->curr_argc_index
#define FG opt->flag_mod
#define H_MOD opt->hash_mod

char *g_hash_mode[CMSSG_ELMT] = {"md5", "MD5", "sha256", "SHA256",
	"sha224", "SHA224", "sha512", "SHA512", "sha384", "SHA384"};
typedef void	(*t_func_t)(UCHAR *data, ULLI len, int fd, int flag_mod);
t_func_t g_func[CMSSG_ELMT] = {
	(t_func_t)&ft_ssl_md5, (t_func_t)&ft_ssl_md5,
	(t_func_t)&ft_ssl_sha256, (t_func_t)&ft_ssl_sha256,
	(t_func_t)&ft_ssl_sha224, (t_func_t)&ft_ssl_sha224,
	(t_func_t)&ft_ssl_sha512, (t_func_t)&ft_ssl_sha512,
	(t_func_t)&ft_ssl_sha384, (t_func_t)&ft_ssl_sha384
};

int			open_file(char *file_name, t_prms *opt)
{
	char p_mode[10];

	if ((opt->fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_printf("ft_ssl: %s: %s: %s\n",
			ft_to_lowercase(ft_memcpy(p_mode, g_hash_mode[H_MOD], 10)),
			file_name, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	open_file_mode(char **argv, int argc, t_prms *opt, UCHAR *data)
{
	int		len;
	char	p_mode[10];

	while (I < argc)
	{
		if (open_file(argv[I], opt) == EXIT_SUCCESS)
		{
			if ((stream_reader(opt->fd, &data[0], 1024, &len)) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (!(opt->flag_mod & FLAG_Q) && !(opt->flag_mod & FLAG_R))
				ft_printf("%s (%s) = ", ft_to_upper_c(
					ft_memcpy(p_mode, g_hash_mode[H_MOD], 10)), argv[I]);
			g_func[opt->hash_mod](&data[0], len, opt->fd, FG);
			if ((opt->flag_mod & FLAG_R) && !(opt->flag_mod & FLAG_Q))
				ft_printf(" %s\n", argv[I]);
		}
		I++;
	}
	return (EXIT_SUCCESS);
}

int			flag_effect(int argc, char **argv, t_prms *opt)
{
	int		len;
	UCHAR	data[1024];

	if (argc == 1 || (H_MOD >= 0 && argc == I) || (opt->flag_mod & FLAG_P))
	{
		if ((stream_reader(0, &data[0], 1024, &len)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		g_func[H_MOD](&data[0], len, STDIN_MODE, FG);
		if (argc == 1)
			ft_printf("FT_SSL> %");
		if (((opt->flag_mod) & FLAG_Q || (opt->flag_mod & FLAG_R)) &&
		I == argc && (opt->flag_mod & FLAG_P))
			g_func[H_MOD]((UCHAR *)"", ft_strlen(argv[I]), STRING_MODE, FG);
	}
	if ((opt->flag_mod & FLAG_S))
		g_func[H_MOD]((UCHAR *)argv[I], ft_strlen(argv[I++]), STRING_MODE, FG);
	if (I < argc && I > 0x1)
		open_file_mode(argv, argc, opt, &data[0]);
	return (EXIT_SUCCESS);
}

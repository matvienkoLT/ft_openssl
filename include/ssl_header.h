/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_header.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:28:48 by lmatvien          #+#    #+#             */
/*   Updated: 2018/10/30 17:28:49 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_HEADER_H
# define SSL_HEADER_H
# include "libft.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <errno.h>
# include "../src/md5/h_md5.h"
# include "../src/sha256/ft_ssl_sha256.h"
# include "../src/sha224/ft_ssl_sha224.h"
# include "../src/sha512/ft_ssl_sha512.h"
# include "../src/sha384/ft_ssl_sha384.h"

# define UCHAR unsigned char
# define FLG_DETECT 1
# define FLG_NFND 0
# define CMSSG_ELMT 10
# define CSTCMMND_ELMT 0
# define CMSSD_ELMN 0
# define FLG_ELCNT 4
# define STRING_MODE -2
# define STDIN_MODE 0

# define MESSAGE_P "echo STDIN to STDOUT and append the checksum to STDOUT"
# define MESSAGE_Q "quiet mode"
# define MESSAGE_R "reverse the format of the output"
# define MESSAGE_S "print the sum of the given string"

char	*g_hash_mode[CMSSG_ELMT];
char	*g_stdrt_comm[CSTCMMND_ELMT];
char	*g_cl_comm[CMSSD_ELMN];
char	*g_flag_mode[FLG_ELCNT];

typedef struct	s_prms
{
	int	hash_mod;
	int flag_mod;
	int	fd;
	int	curr_argc_index;
}				t_prms;

enum			e_flag
{
	FLAG_P = 0x2,
	FLAG_Q = 0x4,
	FLAG_R = 0x8,
	FLAG_S = 0x10
};

int				detect_type_hash(int *h_mode);
int				detect_type_hash_argc(char *data, int *h_mode);
int				stdin_reader(int *h_mode);
void			display_usage(char *data);
int				display_usage_flag(char *data);
int				type_flag(char **argv, int argc, t_prms *opt);
int				open_file(char *file_name, t_prms *opt);
int				stream_reader(int fd, UCHAR *data, int data_size, int *len);
int				flag_effect(int argc, char **argv, t_prms *opt);
#endif

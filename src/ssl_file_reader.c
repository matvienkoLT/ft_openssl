/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_file_reader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatvien <lmatvien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:02:51 by lmatvien          #+#    #+#             */
/*   Updated: 2018/11/09 14:02:52 by lmatvien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_header.h"

int	stream_reader(int fd, UCHAR *data, int data_size, int *len)
{
	if ((*len = read(fd, &data[0], data_size)) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

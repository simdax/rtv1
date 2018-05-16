/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:56:16 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/15 17:21:51 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "./libft/libft.h"
#include <stdlib.h>

static int		count_lines(int fd)
{
	int			j;
	char		*line;

	j = 0;
	while (get_next_line(fd, &line) == 1)
	{
		ft_strdel(&line);
		j++;
	}
	ft_strdel(&line);
	return (j);
}

char			**readcl(char *source, int *i)
{
	char	**kernel_source;
	int		fd;
	int		j;

	fd = 0;
	if ((fd = open(source, O_RDONLY)) > 0)
		j = count_lines(fd);
	close(fd);
	if (!(kernel_source = ft_memalloc(sizeof(char *) * (j + 1))))
		return (NULL);
	j = 0;
	if ((fd = open(source, O_RDONLY)) > 0)
		while (get_next_line(fd, &kernel_source[j]) == 1)
			j++;
	*i = j;
	ft_strdel(&kernel_source[j]);
	close(fd);
	return (kernel_source);
}

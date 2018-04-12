/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:25:33 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/11 18:25:33 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_file_content(char *path)
{
	int		fd;
	int		ret;
	char	buffer[65];
	t_array	*txt;
	char	*file_content;

	txt = array_new(sizeof(char), 8);
	fd = open(path, O_RDONLY);
	if (fd)
	{
		while ((ret = read(fd, buffer, 64)) > 0)
		{
			buffer[ret] = 0;
			array_add(txt, buffer, ret);
		}
	}
	file_content = strdup(txt->mem);
	array_free(txt);
	return (file_content);
}

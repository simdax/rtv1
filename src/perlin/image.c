/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:21:14 by scornaz           #+#    #+#             */
/*   Updated: 2018/06/10 12:21:14 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "perlin.h"

void		write_image(char *path, int width, int height,
						unsigned char *pixels)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd)
	{
		dprintf(fd, "P6\n%d %d\n255\n", width, height);
		write(fd, pixels, width * height * 3);
		close(fd);
	}
}

void		perlin_write_image(t_perlin *perlin, char *path)
{
	write_image(path, perlin->width, perlin->height, perlin->pixels);
}

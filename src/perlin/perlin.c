/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:22:12 by scornaz           #+#    #+#             */
/*   Updated: 2018/06/10 14:26:36 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "perlin.h"
#include "mem.h"

static void		perlin_create_image(t_perlin *perlin)
{
	unsigned char	*pixels;
	float			*image;
	unsigned		i;

	i = 0;
	image = perlin->gen_f(perlin);
	pixels = ft_memalloc(perlin->height * perlin->width * 3 + 1);
	while (i < perlin->width * perlin->height)
	{
		if (image[i] < 0)
			image[i] = -image[i];
		pixels[i * 3] = image[i] * perlin->varia;
		pixels[i * 3 + 1] = image[i] * perlin->varia;
		pixels[i * 3 + 2] = image[i] * perlin->varia;
		++i;
	}
	pixels[i] = 0;
	perlin->pixels = pixels;
	perlin->image = image;
}

t_perlin		*perlin_new(unsigned width, unsigned height, unsigned varia,
							char *path)
{
	t_perlin	*perlin;

	perlin = ft_memalloc(sizeof(t_perlin));
	perlin->path = path;
	perlin->height = height;
	perlin->width = width;
	perlin->varia = varia;
	perlin->gen_f = perlin_generate;
	perlin_create_image(perlin);
	return (perlin);
}

void			perlin_free(t_perlin **perlin)
{
	free((*perlin)->image);
	free((*perlin)->pixels);
	free(*perlin);
	*perlin = 0;
}

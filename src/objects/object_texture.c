/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 12:58:40 by scornaz           #+#    #+#             */
/*   Updated: 2018/06/10 14:40:47 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "object_texture.h"
#include "vec3f.h"
#include <SDL.h>
#include <SDL_image.h>
#include "perlin.h"

int				texture_set(t_obj *obj, char *val)
{
	t_perlin		*perlin;

	obj->texture.name = ft_strdup(val);
	if (ft_strequ(val, "pattern1") ||
		ft_strequ(val, "pattern2") ||
		ft_strequ(val, "pattern3"))
	{
		obj->texture.type = PATTERN;
		obj->texture.pattern = val[7] - '0';
	}
	else
	{
		(void)perlin;
		if (ft_strequ(val, "perlin"))
		{
			perlin = perlin_new(500, 500, 100, "src/perlin/perlin.cl");
			perlin_write_image(perlin, "perlin.ppm"),
			ft_printf("fdshakfh");
			perlin_free(&perlin);
			val = "src/perlin/perlin.ppm";
		}
		if ((obj->texture.surface = IMG_Load(val)))
			obj->texture.type = ASSET;
	}
	return (0);
}

void			print_texture(t_obj_texture *texture)
{
	static char	*types[3] = {"pattern", "file", "none"};

	ft_printf("texture : %s, type -> %s : %p\n",
			texture->name, types[texture->type],
			texture->type == PATTERN ? (unsigned long)texture->pattern :
			(unsigned long)texture->surface);
	if (texture->type == ASSET)
		ft_printf("w : %d, h: %d\n pitch: %d, pixels: %p\n",
				texture->surface->w, texture->surface->h,
				texture->surface->pitch, texture->surface->pixels);
}

void			object_texture(t_obj *obj, t_ray *hit)
{
	if (ft_strequ(obj->tag, "sphere"))
		sphere_texture(hit);
}

static t_vec3f	get_pixel(int *img, int x, int y, int pitch)
{
	unsigned char	*rgb;
	t_vec3f			ret;
	unsigned		pix;

	pix = y * pitch + x * 3;
	rgb = (unsigned char*)(img + pix);
	ret.x = (double)rgb[0] / 255;
	ret.y = (double)rgb[1] / 255;
	ret.z = (double)rgb[2] / 255;
	return (ret);
}

t_vec3f			object_get_texture_pixel(double x, double y, \
		t_obj_texture texture)
{
	t_vec3f		color;
	double		w;
	double		h;

	h = texture.surface->h;
	w = texture.surface->w;
	w /= 3;
	h /= 3.6;
	if (x > 0.9)
		x = 0.9;
	if (y > 0.9)
		y = 0.9;
	color = get_pixel(texture.surface->pixels, x * w, y * h, \
			texture.surface->pitch);
	return (color);
}

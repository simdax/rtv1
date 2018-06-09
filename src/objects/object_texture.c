/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 12:58:40 by scornaz           #+#    #+#             */
/*   Updated: 2018/06/09 17:28:30 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "object_texture.h"
#include "vec3f.h"
#include <SDL.h>
#include <SDL_image.h>

int			texture_set(t_obj *obj, char *val)
{
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
		if (ft_strequ(val, "perlin"))
		{}	// generates perlin
		if ((obj->texture.surface = IMG_Load(val)))
			obj->texture.type = ASSET;
	}
	return (0);
}

void	print_texture(t_obj_texture *texture){
	static	char* types[3] = {"pattern", "file", "none"};

	ft_printf("texture : %s, type -> %s : %p\n",
			  texture->name, types[texture->type],
			  texture->type == PATTERN ? (unsigned long)texture->pattern :
			  (unsigned long)texture->surface
		);
	if (texture->type == ASSET)
		ft_printf("w : %d, h: %d\n pitch: %d, pixels: %p\n",
				texture->surface->w, texture->surface->h,
				texture->surface->pitch, texture->surface->pixels);
}

void		object_texture(t_obj *obj, t_ray *hit)
{
  	t_vec3f	tmp;

	if (ft_strequ(obj->tag, "sphere"))
		sphere_texture(hit);
	/* else if (ft_strequ(obj->tag, "light")) */
	/* 	sphere_normale(obj->obj.sphere, hit); */
	/* else if (ft_strequ(obj->tag, "cone")) */
	/* 	cone_normale(obj->obj.cone, hit); */
	/* else if (ft_strequ(obj->tag, "plane")) */
	/* 	plane_normale(obj->obj.plane, hit); */
	/* else if (ft_strequ(obj->tag, "cylinder")) */
	/* 	cylinder_normale(obj->obj.cylinder, hit); */
}

static t_vec3f	get_pixel(int *img, int x, int y, int pitch)
{
	unsigned char	*rgb;
	t_vec3f			ret;

	unsigned pix = y * pitch + x * 3;
//printf("%f\n", x);
	rgb = (unsigned char*)(img + pix);
	ret.x = (double)rgb[0] / 255;
	ret.y = (double)rgb[1] / 255;
	ret.z = (double)rgb[2] / 255;
	return (ret);
}

t_vec3f		object_get_texture_pixel(double x, double y, t_obj *obj)
{
  	t_vec3f color;

	double w = obj->texture.surface->w;
	double h = obj->texture.surface->h;
	w /= 3;
	h /= 3.6;
	color = get_pixel(obj->texture.surface->pixels, x * w, y * h, obj->texture.surface->pitch);
	return (color);
}

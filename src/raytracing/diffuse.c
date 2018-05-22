/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:07:43 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/22 14:18:02 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_ray	makeray(t_vec3f orig, t_vec3f light_dir)
{
	t_ray		ray;

	ray.tnear = 0;
	ray.rayorig = orig;
	ray.raydir = light_dir;
	return (ray);
}

static void		intersection(int i, t_obj **objects, t_vec3f light_dir, \
		t_ray *hit)
{
	double	solution;
	t_vec3f	orig;
	t_vec3f	normale;
	int		j;
	t_ray	tmp;

	orig = hit->phit;
	normale = hit->nhit;
	vec3f_mul_unit2(&normale, BIAS);
	vec3f_add2(&orig, &normale);
	solution = BIAS;
	j = -1;
	while (objects[++j])
	{
		if (i != j)
		{
			tmp = makeray(orig, light_dir);
			if (object_intersect(objects[j], &tmp, &solution) && \
					solution < hit->max)
			{
				hit->transmission = 0;
				break ;
			}
		}
	}
}

static void		set_surface(t_ray *hit, t_vec3f *light_direction,
						t_obj *object, t_vec3f *emission_light)
{
	double		diffuse;
	double		specular;
	t_vec3f		refraction;
	t_vec3f		object_surface_color;

	object_surface_color = object->surface_color;
	diffuse = fmax(0.0, vec3f_dot(&hit->nhit, light_direction));
	refraction = hit->nhit;
	vec3f_mul_unit2(&refraction, 2 * vec3f_dot(&hit->nhit, light_direction));
	vec3f_sub2(&refraction, light_direction);
	specular = fmax(0.0, vec3f_dot(&refraction, light_direction));
	specular = pow(specular, PHONG);
	if (NO_SHADOW || hit->transmission)
	{
		vec3f_mul2(&object_surface_color, emission_light);
		vec3f_mul_unit2(&object_surface_color, diffuse);
		if (SPEC && !ft_strequ("plane", object->tag))
			vec3f_add_unit2(&object_surface_color, specular);
		vec3f_add2(&hit->color, &object_surface_color);
	}
}

void			diffuse(t_obj **objects, t_obj *object, t_ray *hit)
{
	int		i;
	t_vec3f	light_direction;

	hit->color = (t_vec3f){0, 0, 0};
	i = 0;
	while (objects[i])
	{
		if (ft_strequ(objects[i]->tag, "light"))
		{
			hit->transmission = 1;
			light_direction = objects[i]->position;
			vec3f_sub2(&light_direction, &hit->phit);
			hit->max = length(&light_direction);
			vec3f_normalize(&light_direction);
			intersection(i, objects, light_direction, hit);
			set_surface(hit, &light_direction, object,
						&(objects[i]->emission_color));
		}
		++i;
	}
}

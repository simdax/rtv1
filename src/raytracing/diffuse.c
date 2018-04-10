/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:11:51 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/10 23:39:33 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	intersection(int i, t_obj **objects, t_vec3f light_direction,
						t_ray *hit)
{
	float	t0;
	t_vec3f	orig;
	t_vec3f	normale;
	int		j;

	orig = hit->phit;
	normale = hit->nhit;
	vec3f_mul_unit2(&normale, BIAS);
	vec3f_add2(&orig, &normale);
	t0 = INFINITY;
	j = 0;
	while (objects[j])
	{
		if (i != j)
		{
			if (object_intersect(objects[j], &((t_ray){INFINITY,
								orig, light_direction}), &t0))
			{
				hit->transmission = 0;
				break ;
			}
		}
		++j;
	}
}

static void	set_surface(t_ray *hit, t_vec3f *light_direction,
						t_vec3f object_surface_color, t_vec3f *emission_light)
{
	float		diffuse;
	float		specular;
	t_vec3f		refraction;

	diffuse = fmax(0.0, vec3f_dot(&hit->nhit, light_direction));
	refraction = hit->nhit;
	vec3f_mul_unit2(&refraction, 2 * vec3f_dot(&hit->nhit, light_direction));
	vec3f_sub2(&refraction, light_direction);
	specular = fmax(0.0, vec3f_dot(&refraction, light_direction));
	specular = pow(specular, 16);
//	printf("%f\n", specular);
	if (hit->transmission)
	{
		/* vec3f_print(emission_light); */
		/* printf("diffus %f specular %f\n", diffuse, specular); */
		vec3f_mul2(&object_surface_color, emission_light);
		vec3f_mul_unit2(&object_surface_color, diffuse);
		vec3f_add_unit2(&object_surface_color, specular);
		vec3f_add2(&hit->color, &object_surface_color);
	}
}

void		diffuse(t_obj **objects, t_obj *object, t_ray *hit)
{
	int		i;
	t_vec3f	light_direction;
	float	light_distance;

	hit->color = (t_vec3f){0, 0, 0};
	i = 0;
	while (objects[i])
	{
		if (ft_strequ(objects[i]->tag, "light"))
		{
			hit->transmission = 1;
			light_direction = objects[i]->position;
			vec3f_sub2(&light_direction, &hit->phit);
			vec3f_normalize(&light_direction);
			intersection(i, objects, light_direction, hit);
			set_surface(hit, &light_direction, object->surface_color,
						&(objects[i]->emission_color));
		}
		++i;
	}
}

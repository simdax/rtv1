/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:07:43 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/23 14:48:07 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	intersection(int i, t_obj **objects, t_vec3f light_dir, t_ray *hit)
{
	double	solution;
	t_vec3f	orig;
	t_vec3f	normale;
	int		j;

	orig = hit->phit;
	normale = hit->nhit;
	vec3f_mul_unit2(&normale, BIAS);
	vec3f_add2(&orig, &normale);
	solution = BIAS;
	j = 0;
	while (objects[j])
	{
		if (i != j)
		{
			if (object_intersect(objects[j], &((t_ray){0,
								orig, light_dir}), &solution) && solution < hit->max)
			{
//					printf("intersect avec %d dist : %g >  sol:%g\n", j, hit->max, fabs(solution));
//				vec3f_print(&light_dir);
					//			vec3f_print(&objects[i]->position);
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
	double		diffuse;
	double		specular;
	t_vec3f		refraction;

	diffuse = fmax(0.0, vec3f_dot(&hit->nhit, light_direction));
	refraction = hit->nhit;
	vec3f_mul_unit2(&refraction, 2 * vec3f_dot(&hit->nhit, light_direction));
	vec3f_sub2(&refraction, light_direction);
	specular = fmax(0.0, vec3f_dot(&refraction, light_direction));
	specular = pow(specular, 16);
	if (hit->transmission)
	{
		vec3f_mul2(&object_surface_color, emission_light);
		vec3f_mul_unit2(&object_surface_color, diffuse);
		vec3f_add_unit2(&object_surface_color, specular);
		vec3f_add2(&hit->color, &object_surface_color);
	}
	/* else */
	/* 		vec3f_set(&hit->color, 1, 0, 0); */
}

void		diffuse(t_obj **objects, t_obj *object, t_ray *hit)
{
	int		i;
	t_vec3f	light_direction;
	double	light_distance;

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
			set_surface(hit, &light_direction, object->surface_color,
						&(objects[i]->emission_color));
		}
		++i;
	}
}

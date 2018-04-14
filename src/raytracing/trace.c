/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:01:32 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/14 17:02:34 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline void	search_intersection(t_obj **objects, t_ray *hit)
{
	int		i;
	float	solution;

	i = 0;
	solution = INFINITY;
	while (objects[i])
	{
		if (object_intersect(objects[i], hit, &solution) &&
			solution < hit->tnear)
		{
			hit->tnear = solution;
			hit->obj_index = i;
		}
		++i;
	}
}

static inline void	debug(t_ray *hit)
{
	vec3f_add_unit2(&hit->nhit, 1);
	vec3f_mul_unit2(&hit->nhit, (float)(1 / 2.0));
	vec3f_add2(&hit->color, &hit->nhit);
}

static inline void	ret_surface(t_obj **objects, int depth,
								t_ray *hit, t_vec3f *color)
{
	t_obj	*obj;

	obj = objects[hit->obj_index];
	object_normale(obj, hit);
	hit->color = (t_vec3f){0, 0, 0};
	if (FX && (obj->transparency > 0 ||
				obj->reflection > 0) && depth < MAX_RAY_DEPTH)
		effects(objects, obj, hit, depth);
	else if (DEBUG)
		debug(hit);
	else
		diffuse(objects, obj, hit);
	vec3f_cpy(color, &hit->color);
}

void				trace(t_ray *hit, t_obj **objects,
							int depth, t_vec3f *color)
{
	search_intersection(objects, hit);
	if (hit->obj_index == -1)
		*color = (t_vec3f){BACKGROUND};
	else
		ret_surface(objects, depth, hit, color);
}

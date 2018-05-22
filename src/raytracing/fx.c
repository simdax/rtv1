/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:01:22 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/22 12:21:15 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline double	mix(const double a, const double b, const double mix)
{
	return (b * mix + a * (1 - mix));
}

static inline void		set_surface(t_obj **objects, t_obj *object,
								t_ray *hit, int depth)
{
	double	fresneleffect;
	t_vec3f	tmp;
	t_vec3f	tmp2;
	t_vec3f	tmp3;
	t_ray	ray;

	fresneleffect = mix(pow(1 - hit->facingratio, 3), 1, 0.1);
	vec3f_cpy(&tmp, &hit->nhit);
	vec3f_mul_unit2(&tmp, BIAS);
	vec3f_cpy(&tmp2, &hit->phit);
	vec3f_add2(&tmp2, &tmp);
	ray.tnear = INFINITY;
	ray.rayorig = tmp2;
	ray.raydir = hit->refldir;
	ray.obj_index = -1;
	trace(&(ray), objects, depth + 1, &tmp);
	vec3f_mul_unit2(&tmp, fresneleffect);
	vec3f_cpy(&tmp2, &hit->refraction);
	vec3f_mul_unit2(&tmp2, 1 - fresneleffect * object->transparency);
	vec3f_cpy(&tmp3, &tmp);
	vec3f_add2(&tmp3, &tmp2);
	vec3f_mul2(&tmp3, &object->surface_color);
	vec3f_cpy(&hit->color, &tmp3);
}

static inline void		transparency(t_obj **objects, t_ray *hit, int depth)
{
	t_vec3f		ketos;
	t_vec3f		refrdir;
	t_vec3f		tmp;
	t_ray		ray;

	ketos.x = (hit->inside) ? IOR : 1 / IOR;
	ketos.y = vec3f_dot(&hit->nhit, &hit->raydir);
	ketos.z = 1 - ketos.x * ketos.x * (1 - ketos.y * ketos.y);
	vec3f_cpy(&refrdir, &hit->raydir);
	vec3f_mul_unit2(&refrdir, ketos.x);
	vec3f_cpy(&tmp, &hit->nhit);
	vec3f_mul_unit2(&tmp, ketos.x * ketos.y - sqrt(ketos.z));
	vec3f_add2(&refrdir, &tmp);
	vec3f_normalize(&refrdir);
	vec3f_cpy(&tmp, &hit->nhit);
	vec3f_mul_unit2(&tmp, BIAS);
	vec3f_negate(&tmp);
	vec3f_add2(&tmp, &hit->phit);
	ray.tnear = INFINITY;
	ray.rayorig = tmp;
	ray.raydir = refrdir;
	trace(&(ray), objects, depth + 1, &hit->refraction);
}

void					effects(t_obj **objects, t_obj *object,
							t_ray *hit, int depth)
{
	t_vec3f	tmp;

	hit->facingratio = -vec3f_dot(&hit->raydir, &hit->nhit);
	hit->refraction = (t_vec3f){0, 0, 0};
	vec3f_cpy(&hit->refldir, &hit->raydir);
	vec3f_cpy(&tmp, &hit->nhit);
	vec3f_mul_unit2(&tmp, 2 * vec3f_dot(&hit->raydir, &hit->nhit));
	vec3f_sub2(&hit->refldir, &tmp);
	vec3f_normalize(&hit->refldir);
	if (object->transparency > 0)
		transparency(objects, hit, depth);
	set_surface(objects, object, hit, depth);
}

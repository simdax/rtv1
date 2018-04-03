/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:11:13 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/03 12:24:31 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline float	mix(const float a, const float b, const float mix)
{
	return (b * mix + a * (1 - mix));
}

static inline void	set_surface(t_obj **objects, t_obj *object,
								t_ray *hit, int depth)
{
	float	fresneleffect;
	t_vec3f	tmp;
	t_vec3f	tmp2;
	t_vec3f	tmp3;

	fresneleffect = mix(pow(1 - hit->facingratio, 3), 1, 0.1);
	vec3f_cpy(&tmp, &hit->nhit);
	vec3f_mul_unit2(&tmp, BIAS);
	vec3f_cpy(&tmp2, &hit->phit);
	vec3f_add2(&tmp2, &tmp);
	trace(&((t_ray){INFINITY, tmp2, hit->refldir, -1}), objects,
		depth + 1, &tmp);
	vec3f_mul_unit2(&tmp, fresneleffect);
	vec3f_cpy(&tmp2, &hit->refraction);
	vec3f_mul_unit2(&tmp2, 1 - fresneleffect * object->transparency);
	vec3f_cpy(&tmp3, &tmp);
	vec3f_add2(&tmp3, &tmp2);
	vec3f_mul2(&tmp3, &object->surface_color);
	vec3f_cpy(&hit->color, &tmp3);
}

static inline void	transparency(t_obj **objects, t_ray *hit, int depth)
{
	float		eta;
	float		cosi;
	float		k;
	t_vec3f		refrdir;
	t_vec3f		tmp;

	eta = (hit->inside) ? IOR : 1 / IOR;
	cosi = vec3f_dot(&hit->nhit, &hit->raydir);
	k = 1 - eta * eta * (1 - cosi * cosi);
	vec3f_cpy(&refrdir, &hit->raydir);
	vec3f_mul_unit2(&refrdir, eta);
	vec3f_cpy(&tmp, &hit->nhit);
	vec3f_mul_unit2(&tmp, eta * cosi - sqrt(k));
	vec3f_add2(&refrdir, &tmp);
	vec3f_normalize(&refrdir);
	vec3f_cpy(&tmp, &hit->nhit);
	vec3f_mul_unit2(&tmp, BIAS);
	vec3f_negate(&tmp);
	vec3f_add2(&tmp, &hit->phit);
	trace(&((t_ray){INFINITY, tmp, refrdir}), objects,
		depth + 1, &hit->refraction);
}

void				effects(t_obj **objects, t_obj *object,
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

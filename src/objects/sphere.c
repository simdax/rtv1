/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:38:55 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/25 16:19:25 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "ray.h"

t_sphere	*sphere_new(t_vec3f center, double radius)
{
	t_sphere	*ret;

	ret = malloc(sizeof(t_sphere));
	ret->center = center;
	ret->radius = radius;
	ret->radius2 = radius * radius;
	return (ret);
}

int			sphere_intersect(t_sphere *sphere, t_ray *hit, double *res)
{
	double		thc;
	double		tca;
	double		d2;
	t_vec3f		l;

	vec3f_cpy(&l, &sphere->center);
	vec3f_sub2(&l, &hit->rayorig);
	tca = vec3f_dot(&l, &hit->raydir);
	if (tca < 0)
		return (0);
	d2 = vec3f_dot(&l, &l) - tca * tca;
	if (d2 > sphere->radius2)
		return (0);
	thc = sqrt(sphere->radius2 - d2);
	if ((*res = tca - thc) < 0)
		*res = tca + thc;
	return (1);
}

void		sphere_normale(t_sphere *sphere, t_ray *hit)
{
	vec3f_sub2(&hit->nhit, &(sphere->center));
}

void		sphere_texture(t_ray *hit)
{
  	hit->texture.x = (1 + atan2(hit->nhit.z, hit->nhit.x) / M_PI) * 0.5;
  	hit->texture.y = acosf(hit->nhit.y) / M_PI;
}

void		sphere_print(t_sphere *sphere)
{
	ft_printf("centre : ");
	vec3f_print(&sphere->center);
	ft_printf("radius: ");
	ft_putfloat(sphere->radius);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:48:28 by scornaz           #+#    #+#             */
/*   Updated: 2018/06/09 16:48:31 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "ray.h"

t_sphere	*sphere_new(t_vec3f center, double radius)
{
	t_sphere	*ret;

	ret = ft_memalloc(sizeof(t_sphere));
	ret->center = center;
	ret->radius = radius;
	ret->radius2 = radius * radius;
	return (ret);
}

int			sphere_intersect(t_sphere *sphere, t_ray *hit, double *res, \
		t_vec3f *pos)
{
	double		thc;
	double		tca;
	double		d2;
	t_vec3f		l;

	vec3f_cpy(&l, pos);
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
/* 	t_vec3f Vn = (t_vec3f){0, 1, 0}; */
/* 	t_vec3f Ve = vec3f_cross(&Vn, &hit->nhit); */
/* 	double phi = acos( -vec3f_dot( &Vn, &hit->nhit )); */
/* 	double theta = ( acos( vec3f_dot( &hit->nhit, &Ve ) / sin(phi)) ) / ( 2 * M_PI); */
/* 	hit->texture.x = phi / M_PI; */
/* 	t_vec3f Vnn = vec3f_cross( &Vn, &Ve ); */
/* //	printf("%f\n", theta); */
/* //	vec3f_print(&Ve); */
/* 	if ( vec3f_dot( &Vnn, &hit->nhit ) > 0 ) */
/* 		hit->texture.y = theta; */
/* 	else */
/* 		hit->texture.y = 1 - theta; */
	hit->texture.x = 0.5 + atan2(hit->nhit.z, hit->nhit.x) / (2 * M_PI);
	hit->texture.y = 0.5 - asin(hit->nhit.y) / M_PI;
	//printf("%f %f ''' \n", x, y); fflush(stdout);

  	/* hit->texture.x = (1 + atan2(hit->nhit.z, hit->nhit.x) / M_PI) * 0.5; */
  	/* hit->texture.y = acos(hit->nhit.y) / M_PI; */
}

void		sphere_print(t_sphere *sphere)
{
	ft_printf("centre : ");
	vec3f_print(&sphere->center);
	ft_printf("radius: ");
	ft_putfloat(sphere->radius);
}

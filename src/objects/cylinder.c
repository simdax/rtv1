/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:34:42 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/17 10:40:47 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

t_cylinder	*cylinder_new(t_vec3f position, t_vec3f axis,
							double radius)
{
	t_cylinder	*cyl;

	cyl = malloc(sizeof(t_cylinder));
	cyl->axis = axis;
	cyl->radius = radius;
	cyl->radius2 = radius * radius;
	return (cyl);
}

int			cylinder_intersect(t_cylinder *cylinder, t_ray *hit, \
		double *res)
{
	return (resolve_quadratic((t_vec3f){
				vec3f_dot(&hit->raydir, &hit->raydir) -
					pow(vec3f_dot(&hit->raydir, &cylinder->axis), 2),
					2 * (vec3f_dot(&hit->raydir, &hit->distance) -
							vec3f_dot(&hit->raydir, &cylinder->axis) *
							vec3f_dot(&hit->distance, &cylinder->axis)),
					vec3f_dot(&hit->distance, &hit->distance) -
					pow(vec3f_dot(&hit->distance, &cylinder->axis), 2) -
					cylinder->radius2
					}, res));
}

void		cylinder_normale(t_cylinder *cylinder, t_ray *hit)
{
	t_vec3f uv;

	vec3f_sub2(&hit->nhit, &cylinder->position);
	vec3f_cpy(&uv, &cylinder->axis);
	vec3f_mul_unit2(&uv, vec3f_dot(&cylinder->axis, &hit->nhit));
	vec3f_sub2(&hit->nhit, &uv);
}

void		cylinder_print(t_cylinder *cylinder)
{
	ft_printf("radius: ");
	ft_putfloat(cylinder->radius);
	ft_printf("\naxis:");
	vec3f_print(&cylinder->axis);
}

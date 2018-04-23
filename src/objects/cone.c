/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:58:43 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/23 12:13:52 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"

t_cone		*cone_new(double angle, double height,
					t_vec3f tip_position, t_vec3f axis)
{
	t_cone	*cone;

	cone = malloc(sizeof(t_cone));
	cone->angle = angle;
	cone->angle2 = angle * angle;
	cone->tan_angle = tan(angle / 2);
	cone->tan_angle2 = 1 + cone->tan_angle * cone->tan_angle;
	cone->height = height;
	cone->tip_position = tip_position;
	cone->axis = axis;
	return (cone);
}

int			cone_intersect(t_cone *cone, t_ray *hit, double *res)
{
	double	k;
	double	dir_axis;
	double	dist_axis;

	k = cone->tan_angle2;
	dir_axis = vec3f_dot(&hit->raydir, &cone->axis);
	dist_axis = vec3f_dot(&hit->distance, &cone->axis);
	return (resolve_quadratic((t_vec3f){
				vec3f_dot(&hit->raydir, &hit->raydir) - k * pow(dir_axis, 2),
					2 * (vec3f_dot(&hit->raydir, &hit->distance)
					- k * dir_axis * dist_axis),
					vec3f_dot(&hit->distance, &hit->distance)
					- k * pow(dist_axis, 2)
					}, res));
}

void		cone_normale(t_cone *cone, t_ray *hit)
{
	double	dist_to_apex;
	t_vec3f	axis;
	t_vec3f	hit_cpy;

	hit_cpy = hit->phit;
	vec3f_sub2(&hit_cpy, &cone->tip_position);
	axis = cone->axis;
	if (vec3f_dot(&cone->axis, &hit_cpy) < 0)
	{
			vec3f_negate(&axis);
			dist_to_apex = length(&hit_cpy) / cos(cone->angle / 2);
	}
	else
			dist_to_apex = length(&hit_cpy) / cos(cone->angle / 2);
	vec3f_mul_unit2(&axis, dist_to_apex);
	vec3f_add2(&axis, &cone->tip_position);
	vec3f_sub2(&axis, &hit->phit);
	vec3f_cpy(&hit->nhit, &axis);
}

void		cone_print(t_cone *cone)
{
	ft_printf("position : ");
	vec3f_print(&cone->tip_position);
	ft_printf("axis : ");
	vec3f_print(&cone->axis);
	ft_printf("angle : %g\n", cone->angle);
	ft_printf("height : %g\n", cone->height);
}

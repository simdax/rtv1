/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:37:17 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/03 12:07:48 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

t_plane			*plane_new(t_vec3f position, t_vec3f normale)
{
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	plane->position = position;
	plane->axis = normale;
	return (plane);
}

void			plane_print(t_plane *plane)
{
	printf("normale :");
	vec3f_print(&plane->axis);
}

int				plane_intersect(t_plane *plane, t_ray *hit, float *res)
{
	float		dist_axis;
	float		dir_axis;
	float		result;

	dir_axis = vec3f_dot(&plane->axis, &hit->raydir);
	if (dir_axis > 0)
	{
		dist_axis = vec3f_dot(&hit->distance, &plane->axis);
		result = -dist_axis / dir_axis;
		if (result >= 0)
		{
			*res = result;
			return (1);
		}
		return (0);
	}
	return (0);
}

inline void		plane_normale(t_plane *plane, t_ray *hit)
{
	vec3f_cpy(&hit->nhit, &plane->axis);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:37:40 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/03 11:42:00 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "vec3f/vec3f.h"
# include "ray.h"

typedef struct	s_plane{
	t_vec3f		position;
	t_vec3f		axis;
}				t_plane;

t_plane			*plane_new(t_vec3f position, t_vec3f normale);
int				plane_intersect(t_plane *plane, t_ray *hit, float *t0);
void			plane_print(t_plane *plane);
void			plane_normale(t_plane *plane, t_ray *hit);

#endif

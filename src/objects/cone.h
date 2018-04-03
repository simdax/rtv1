/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:33:55 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/03 11:38:18 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "vec3f/vec3f.h"
# include "ray.h"
# include "resolvequadratics.h"

typedef struct	s_cone
{
	float		angle;
	float		angle2;
	float		height;
	t_vec3f		tip_position;
	t_vec3f		axis;
	float		tan_angle;
	float		tan_angle2;
}				t_cone;

t_cone			*cone_new(float angle, float height,
						t_vec3f tip_position, t_vec3f axis);
int				cone_intersect(t_cone *cone, t_ray *hit, float *t0);
void			cone_print(t_cone *cone);
void			cone_normale(t_cone *cone, t_ray *hit);

#endif

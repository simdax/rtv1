/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:34:56 by scornaz           #+#    #+#             */
/*   Updated: 2018/06/09 10:30:18 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "vec3f/vec3f.h"
# include "ray.h"
# include "resolve_quadratics.h"

typedef struct	s_cylinder{
	t_vec3f		position;
	t_vec3f		axis;
	double		radius;
	double		radius2;
}				t_cylinder;

t_cylinder		*cylinder_new(t_vec3f	position, t_vec3f axis,
							double radius);
int				cylinder_intersect(t_cylinder *cylinder,
							t_ray *hit, double *t0);
void			cylinder_print(t_cylinder *cylinder);
void			cylinder_normale(t_cylinder *cylinder, t_ray *hit);
void			cylinder_texture(t_ray *hit);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:34:56 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/02 14:35:05 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
#define CYLINDER_H

# include "vec3f/vec3f.h"

typedef struct	s_cylinder{
	t_vec3f		position;
	t_vec3f     axis;
	float		radius;
	float		radius2;
}		t_cylinder; 

# include "object.h"

t_cylinder	*cylinder_new(t_vec3f	position, t_vec3f axis,
						  float radius);
int			cylinder_intersect(t_cylinder *cylinder,
						   t_ray *hit, float *t0);
void		cylinder_print(t_cylinder *cylinder);
void    	cylinder_normale(t_cylinder *cylinder, t_ray *hit);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_fini.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:48:57 by cbesse            #+#    #+#             */
/*   Updated: 2018/05/11 19:51:22 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYL_FINI_H
# define CYL_FINI_H

# include "vec3f/vec3f.h"
# include "ray.h"
#	include "plane.h"

typedef struct	s_fcylinder
{
	t_vec3f	base;
	t_vec3f	dir;
	double		radius;
	double		radius2;
	double		size;
	t_plane   *plan1;
	t_plane		*plan2;
	int				plan;

}				t_fcylinder;

t_fcylinder	*fcylindre_new(t_vec3f position, t_vec3f axis,
		double radius, double size);
int				fcylinder_intersect(t_fcylinder *fcyl, t_ray *hit, double *t0);
void			fcylindre_print(t_fcylinder *fcyl);
void			fcylinder_normale(t_fcylinder *fcyl, t_ray *hit);
void fcylsetplan(t_fcylinder *fcyl);
#endif

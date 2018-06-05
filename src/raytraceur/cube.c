/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 12:56:16 by cbesse            #+#    #+#             */
/*   Updated: 2018/06/05 12:56:17 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			hit_cube(t_ray2 *ray, double *min_max, t_record *rec)
{
	t_vecteur	oc;
	double		d;
	double		temp;

	oc = v_less(ray->ori, plan->point);
	d = v_dot(ray->dir, plan->vdir);
	if (d != 0)
	{
		temp = -v_dot(oc, plan->vdir) / d;
		if (temp < min_max[1] && temp > min_max[0] && plan_ok(ray, plan, temp))
		{
			rec->t = temp;
			rec->p = v_add(ray->ori, v_mult(ray->dir, rec->t));
			rec->normal = v_normalize(v_set(plan->vdir.x, plan->vdir.y, \
						plan->vdir.z));
			if (v_dot(ray->dir, plan->vdir) > 0)
				setrec(rec);
			return (1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:02:46 by cbesse            #+#    #+#             */
/*   Updated: 2018/05/24 18:27:29 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	setrec(t_record *rec)
{
	rec->normal.x = -rec->normal.x;
	rec->normal.y = -rec->normal.y;
	rec->normal.z = -rec->normal.z;
	rec->inside = 1;
}

int test_square(t_vecteur p, t_plan *plan , t_ray2 *ray)
{
	t_vecteur p1;
	t_vecteur p2;
	t_vecteur p3;
	t_vecteur p4;
	t_vecteur n;

	double x;
	double size = 1;
	double y;
	n = v_set(plan->vdir.x, plan->vdir.y, plan->vdir.z);
	if (v_dot(ray->dir, plan->vdir) > 0)
		n = v_negate(n);

	//X = (q-p1).(p2-p1) / ||(p2-p1)||
	//Y = (q-p1).(p3-p1) / ||(p3-p1)||
	p1 = v_set(size * (1 - n.x) ,size * (1 - n.y) ,size * (1 - n.z));
	p2 = v_set(-size * (1 - n.x) ,size * (1 - n.y) ,size * (1 - n.z));
	p3 = v_set(size * (1 - n.x) ,-size * (1 - n.y) ,size * (1 - n.z));
	p4 = v_set(-size * (1 - n.x) ,-size * (1 - n.y) ,size * (1 - n.z));

	x = v_dot(v_less(p, p1), v_less(p2, p1)) / v_norm(v_less(p2, p1));
	y = v_dot(v_less(p, p1), v_less(p3, p1)) / v_norm(v_less(p3, p1));
	if(x >= 0 && x <= 1 && y >= 0 && y <= 1)
	 	return(1);
	return(0);


}

int			plan_ok(t_ray2 *ray, t_plan *plan, double t)
{
	t_vecteur	p;
	double		ok;

	p = v_add(ray->ori, v_mult(ray->dir, t));
	ok = v_norm(v_less(plan->point, p));
	if (ok <= plan->size || plan->size == 0)
		return (1);
	//if (test_square(p, plan, ray))
	//	return(1);
	return (0);
}

int			hit_plan(t_plan *plan, t_ray2 *ray, double *min_max, t_record *rec)
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

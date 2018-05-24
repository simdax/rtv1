/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre_fini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 17:03:44 by cbesse            #+#    #+#             */
/*   Updated: 2018/05/24 16:46:48 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "object.h"

void	fcyl_rec(t_ray2 *ray, double t, t_fcylindre *fcyl, t_record *rec)
{
	t_vecteur	uv;
	t_vecteur	oc;

	rec->t = t;
	rec->p = v_add(ray->ori, v_mult(ray->dir, rec->t));
	oc = v_less(rec->p, fcyl->base);
	uv = v_mult(fcyl->dir, v_dot(fcyl->dir, oc));
	rec->normal = v_normalize(v_less(oc, uv));
}

int		fcyl_test(t_ray2 *ray, t_fcylindre *fcyl, double t)
{
	t_vecteur	uv;
	t_vecteur	oc;
	t_vecteur	p;
	t_vecteur	normal;
	double		ok;

	p = v_add(ray->ori, v_mult(ray->dir, t));
	oc = v_less(p, fcyl->base);
	uv = v_mult(fcyl->dir, v_dot(fcyl->dir, oc));
	normal = v_normalize(v_less(oc, uv));
	p = v_less(p, (v_less(oc, uv)));
	ok = v_norm(v_less(p, fcyl->base));
	if (ok <= fcyl->size / 2)
		return (1);
	return (0);
}

int	hit_fcylbord(t_fcylindre *fcyl, t_ray2 *ray, double *min_max, t_record *rec)
{
	int	t;
	int	p;

	if (rec->f == 1 && (t = hit_plan(fcyl->plan1, ray, min_max, rec)))
	{
		set_min_max(min_max[0], rec->t, min_max);
		return (t);
	}
	if (rec->f == 2 && (p = hit_plan(fcyl->plan2, ray, min_max, rec)))
	{
		set_min_max(min_max[0], rec->t, min_max);
		return (p);
	}
	return (0);
}

int	hit_fcylindre(t_fcylindre *fcyl, t_ray2 *ray, double *min_max, t_record *rec)
{
	t_vecteur	x;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		r;

	x = v_less(ray->ori, fcyl->base);
	a = v_dot(ray->dir, ray->dir) - pow(v_dot(ray->dir, fcyl->dir), 2);
	b = 2 * (v_dot(ray->dir, x) - v_dot(ray->dir, fcyl->dir) * v_dot(x, fcyl->dir));
	c = v_dot(x, x) - pow(v_dot(x, fcyl->dir), 2) - fcyl->radius * fcyl->radius;
	disc = b * b - 4 * a * c;
	if (disc > 0)
	{
		r = (-1 * b - sqrt(disc)) / (2 * a);
		if (r < min_max[1] && r > min_max[0] && fcyl_test(ray, fcyl, r) == 1)
		{
			fcyl_rec(ray, r, fcyl, rec);
			return (1);
		}
		rec->f = 1;
		if (hit_fcylbord(fcyl, ray, min_max, rec))
			return (1);
		rec->f = 2;
		if (hit_fcylbord(fcyl, ray, min_max, rec))
			return (1);
		r = (-1 * b + sqrt(disc)) / (2 * a);
		if (r < min_max[1] && r > min_max[0] && fcyl_test(ray, fcyl, r) == 1)
		{
			fcyl_rec(ray, r, fcyl, rec);
			return (1);
		}
	}
	return (0);
}

void	fcylindre_def2(t_fcylindre *fcyl, t_fcylinder *cyl)
{
	fcyl->base.x = cyl->base.x;
	fcyl->base.y = cyl->base.y;
	fcyl->base.z = cyl->base.z;
	fcyl->radius = cyl->radius;
	fcyl->size = cyl->size;
	fcyl->dir.x = cyl->dir.x;
	fcyl->dir.y = cyl->dir.y;
	fcyl->dir.z = cyl->dir.z;
	fcyl->dir = v_normalize(fcyl->dir);
	fcyl->plan1 = (t_plan *)ft_memalloc(sizeof(t_plan));
	fcyl->plan2 = (t_plan *)ft_memalloc(sizeof(t_plan));
	fcyl->plan1->point = v_add(fcyl->base, v_mult(fcyl->dir, fcyl->size / 2));
	fcyl->plan2->point = v_less(fcyl->base, v_mult(fcyl->dir, fcyl->size / 2));
	fcyl->plan1->vdir = v_set(fcyl->dir.x, fcyl->dir.y, fcyl->dir.z);
	fcyl->plan2->vdir = v_set(-fcyl->dir.x, -fcyl->dir.y, -fcyl->dir.z);
	fcyl->plan1->size = fcyl->radius;
	fcyl->plan2->size = fcyl->radius;
}

void		fcylindre_def(t_obj *obj, t_scene *scene)
{
	int j;

	j = 0;
	scene->list[scene->i].form =
		(t_fcylindre *)ft_memalloc(sizeof(t_fcylindre));
	fcylindre_def2(scene->list[scene->i].form, obj->obj.fcylinder);
	scene->list[scene->i].color.x = obj->surface_color.x;
	scene->list[scene->i].color.y = obj->surface_color.y;
	scene->list[scene->i].color.z = obj->surface_color.z;
	scene->list[scene->i].ks = obj->reflection;
	scene->list[scene->i].kt = obj->transparency;
	scene->list[scene->i].type = 5;
	scene->list[scene->i].index = scene->i;
	scene->i++;
	while (j < scene->i)
		scene->list[j++].size = scene->i;
}

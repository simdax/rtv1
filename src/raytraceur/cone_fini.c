/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_fini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 19:07:50 by cbesse            #+#    #+#             */
/*   Updated: 2018/05/10 19:07:51 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "object.h"

void	fcone_rec(t_ray2 *ray, double t, t_fcone *cone, t_record *rec)
{
	double		uv;
	t_vecteur	temp;
	t_vecteur	oc;

	rec->t = t;
	rec->p = v_add(ray->ori, v_mult(ray->dir, rec->t));
	oc = v_less(rec->p, cone->apex);
	if (v_dot(v_normalize(cone->dir), v_normalize(oc)) > 0)
		temp = v_set(cone->dir.x, cone->dir.y, cone->dir.z);
	else
		temp = v_set(-cone->dir.x, -cone->dir.y, -cone->dir.z);
	uv = v_norm(oc) / cos(cone->angle / 2);
	rec->normal = v_normalize(v_less(oc, v_mult(temp, uv)));
	if (v_dot(ray->dir, rec->normal) > 0)
		rec->inside = 1;
}

double	fconepv(t_ray2 *ray, t_fcone *fcone, t_record *rec, double t)
{
	double uv;
  t_vecteur p;
	t_vecteur oc;
	double k;
	k = fcone->angle / 2;

	p = v_add(ray->ori, v_mult(ray->dir, t));
	oc = v_less(p, fcone->apex);
	uv = v_norm(oc) * cos(k);
	return(uv);
}

int fcone_test(t_ray2 *ray, t_fcone *fcone, t_record *rec, double t)
{
  double ok;
	t_vecteur p;

	p = v_add(ray->ori, v_mult(ray->dir, t));
	ok = fconepv(ray, fcone, rec, t);
	ok = v_dot(fcone->dir, v_normalize(v_less(p, fcone->apex))) < 0 ? -ok : ok;
	if (ok <= fcone->mid + fcone->size/2 && ok >= fcone->mid - fcone->size/2)
    return(1);
  return(0);
}

int	hit_fconebord(t_fcone *fcone, t_ray2 *ray, double *min_max, t_record *rec, int f)
{
	int t;
	int p;

  if (fcone->plan1->size != 0)
		if(f == 1 && (t = hit_plan(fcone->plan1, ray, min_max, rec)))
		{
			set_min_max(min_max[0], rec->t, min_max);
			return (t);
		}
  if (fcone->plan2->size != 0)
		if(f == 2 && (p = hit_plan(fcone->plan2, ray, min_max, rec)))
		{
			set_min_max(min_max[0], rec->t, min_max);
			return (p);
		}
	return(0);
}

int	hit_fcone(t_fcone *fcone, t_ray2 *ray, double *min_max, t_record *rec)
{
  double a;
  double b;
  double c;
  double disc;
  double r;
  double k;
  t_vecteur x;

  k = tan(fcone->angle / 2);
  k = k * k;
  x = v_less(ray->ori, fcone->apex);
  a = v_dot(ray->dir, ray->dir) - (1 + k) * pow(v_dot(ray->dir, fcone->dir), 2);
  b = 2 * (v_dot(ray->dir, x) - (1 + k) * v_dot(ray->dir, fcone->dir) * v_dot(x, fcone->dir));
  c = v_dot(x, x) - (1 + k) * (pow(v_dot(x, fcone->dir), 2));
  disc = b * b - 4 * a * c;
	if (disc > 0)
	{
	  r = (-1 * b - sqrt(disc)) / (2 * a);
	  if (r < min_max[1] && r > min_max[0] && fcone_test(ray, fcone, rec, r) == 1)
	  {
	    fcone_rec(ray, r, fcone, rec);
	    return (1);
	  }
	  if (hit_fconebord(fcone, ray, min_max, rec, 1))
	      return(1);
	  if (hit_fconebord(fcone, ray, min_max, rec, 2))
	    return(1);
	  r = (-1 * b + sqrt(disc)) / (2 * a);
	  if (r < min_max[1] && r > min_max[0] && fcone_test(ray, fcone, rec, r) == 1)
	  {
	    fcone_rec(ray, r, fcone, rec);
	    return (1);
	  }
	}
  return(0);
}


void	def_fcone2(t_fcone *fcone, t_fcone2 *cone)
{
	t_vecteur h1;
	t_vecteur h2;

	fcone->apex.x = cone->tip_position.x;
	fcone->apex.y = cone->tip_position.y;
	fcone->apex.z = cone->tip_position.z;
	fcone->angle = cone->angle * M_PI / 180;
	fcone->dir.x = cone->axis.x;
	fcone->dir.y = cone->axis.y;
	fcone->dir.z = cone->axis.z;
	fcone->dir = v_normalize(fcone->dir);
  fcone->size = cone->size;
	fcone->mid = cone->mid;
  h1 = v_mult(fcone->dir, fcone->mid + fcone->size/2);
  h2 = v_mult(fcone->dir, fcone->mid - fcone->size/2);
	fcone->plan1 = (t_plan *)ft_memalloc(sizeof(t_plan));
	fcone->plan2 = (t_plan *)ft_memalloc(sizeof(t_plan));
	fcone->plan1->point = v_add(fcone->apex, v_mult(fcone->dir, fcone->mid + fcone->size/2));
	fcone->plan2->point = v_add(fcone->apex, v_mult(fcone->dir, fcone->mid - fcone->size/2));
	fcone->plan1->vdir = v_set(fcone->dir.x, fcone->dir.y, fcone->dir.z);
	fcone->plan2->vdir = v_set(-fcone->dir.x, -fcone->dir.y, -fcone->dir.z);
	fcone->plan1->size = sqrt(fabs(pow(v_norm(h1),2) - pow(v_norm(h1) / cos(fcone->angle/2),2)));
	fcone->plan2->size = sqrt(fabs(pow(v_norm(h2),2) - pow(v_norm(h2) / cos(fcone->angle/2),2)));
}

void		def_fcone(t_obj *obj, t_scene *scene)
{
	int j;

	j = 0;
	scene->list[scene->i].form = (t_fcone *)ft_memalloc(1 * sizeof(t_fcone));
	def_fcone2(scene->list[scene->i].form, obj->obj.fcone2);
	scene->list[scene->i].color.x = obj->surface_color.x;
	scene->list[scene->i].color.y = obj->surface_color.y;
	scene->list[scene->i].color.z = obj->surface_color.z;
	scene->list[scene->i].ks = obj->reflection;
	scene->list[scene->i].kt = obj->transparency;
	scene->list[scene->i].type = 6;
	scene->i++;
	while (j < scene->i)
		scene->list[j++].size = scene->i;
}

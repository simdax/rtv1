/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_fini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:29:22 by cbesse            #+#    #+#             */
/*   Updated: 2018/05/11 19:32:29 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "cyl_fini.h"


t_fcylinder	*fcylindre_new(t_vec3f position, t_vec3f dir,
		double radius, double size)
{
	t_fcylinder	*fcyl;

	fcyl = (t_fcylinder *)ft_memalloc(sizeof(t_fcylinder));
	fcyl->dir = dir;
  fcyl->base = position;
	fcyl->radius = radius;
	fcyl->size = size;
	/*fcyl->plan1->position = fcyl->dir;
	vec3f_mul_unit2(&fcyl->plan1->position, fcyl->size/2);
	vec3f_add2(&fcyl->plan1->position, &fcyl->base);
	fcyl->plan2->position = fcyl->dir;
	vec3f_mul_unit2(&fcyl->plan2->position, -fcyl->size/2);
	vec3f_add2(&fcyl->plan2->position, &fcyl->base);
	//fcyl->plan1->position = v_add(fcyl->base, v_mult(fcyl->dir, fcyl->size/2));
	//fcyl->plan2->position = v_less(fcyl->base, v_mult(fcyl->dir, fcyl->size/2));
	printf("plan 2 = ");
	vec3f_print(&fcyl->plan2->position);
	printf("\n");
	printf("plan 1 = ");
	vec3f_print(&fcyl->plan1->position);
	printf("\n");
	fcyl->plan1->axis = fcyl->dir;
	fcyl->plan2->axis = fcyl->dir;
	vec3f_negate(&fcyl->plan2->axis);
	fcyl->plan1->size = fcyl->radius;
	fcyl->plan2->size = fcyl->radius;*/
	return (fcyl);
}
/*
void fcylsetplan(t_fcylinder *fcyl)
{
	//fcyl->plan1 = (t_plane *)ft_memalloc(sizeof(t_plane));
	//fcyl->plan2 = (t_plane *)ft_memalloc(sizeof(t_plane));
	fcyl->plan1->position = fcyl->dir;
	vec3f_mul_unit2(&fcyl->plan1->position, fcyl->size/2);
	vec3f_add2(&fcyl->plan1->position, &fcyl->base);
	fcyl->plan2->position = fcyl->dir;
	vec3f_mul_unit2(&fcyl->plan2->position, -fcyl->size/2);
	vec3f_add2(&fcyl->plan2->position, &fcyl->base);
	//fcyl->plan1->position = v_add(fcyl->base, v_mult(fcyl->dir, fcyl->size/2));
	//fcyl->plan2->position = v_less(fcyl->base, v_mult(fcyl->dir, fcyl->size/2));
	printf("plan 2 = ");
	vec3f_print(&fcyl->plan2->position);
	printf("\n");
	printf("plan 1 = ");
	vec3f_print(&fcyl->plan1->position);
	printf("\n");
	fcyl->plan2->axis = fcyl->dir;
	fcyl->plan1->axis = fcyl->dir;
	vec3f_negate(&fcyl->plan2->axis);
	vec3f_normalize2(&fcyl->plan2->axis);
	vec3f_normalize2(&fcyl->plan1->axis);
	fcyl->plan1->size = fcyl->radius;
	fcyl->plan2->size = fcyl->radius;
}


// WIP
int fcyl_test(t_ray *hit, t_fcylinder *fcyl, double t)
{
  t_vec3f uv;
	t_vec3f oc;
  t_vec3f pa;
  t_vec3f normal;
  t_vec3f p;
  t_vec3f tmp;
  double ok;

  p = hit->rayorig;
  tmp = hit->raydir;
  vec3f_mul_unit2(&tmp, t);
  vec3f_add2(&p, &tmp);
  oc = p;
	vec3f_sub2(&oc, &fcyl->base);
  uv = fcyl->dir;
	vec3f_mul_unit2(&uv, vec3f_dot(&fcyl->dir, &oc));
  vec3f_sub2(&oc, &uv);
  vec3f_sub2(&p, &oc);
  vec3f_sub2(&p, &fcyl->base);
  ok = length(&p);

  //ok = v_norm(v_less(pa, fcyl->base));
  if (ok <= fcyl->size / 2)
    return(1);
  return(0);
}
//ok?

int	hit_fcylbord(t_fcylinder *fcyl, t_ray *hit, double *res, int f)
{

	int t;
	int p;
	//printf("%f, %f ,%f\n" ,fcyl->plan2->axis.x,fcyl->plan2->axis.y,fcyl->plan2->axis.z);
	if(f == 1 && (t = plane_intersect(fcyl->plan1, hit, res)))
	{
		//printf("touche plan 1\n"); fflush(stdout);
		//set_min_max(min_max[0], rec->t, min_max);
		/res = t;
		//fcyl->plan = 1;
		return (t);
	}
	if(f == 2 && (p = plane_intersect(fcyl->plan2, hit, res)))
	{
		//fcyl->plan = 2;
//		printf("touche plan 2\n"); fflush(stdout);

	//	set_min_max(min_max[0], rec->t, min_max);
		/res = p;
		return (p);
	}
	return(0);
}

int			fcylinder_intersect(t_fcylinder *fcyl, t_ray *hit,
		double *res)
{
	t_vec3f	x;
	double a;
	double b;
	double c;
	double disc;
	double r;

	//fcyl->plan = 0;
  x = hit->rayorig;
  vec3f_sub2(&x, &fcyl->base);
  a = vec3f_dot(&hit->raydir, &hit->raydir) - pow(vec3f_dot(&hit->raydir, &fcyl->dir),2);
  b = 2 * (vec3f_dot(&hit->raydir, &x) - vec3f_dot(&hit->raydir, &fcyl->dir) * vec3f_dot(&x, &fcyl->dir));
  c = vec3f_dot(&x, &x) - pow(vec3f_dot(&x, &fcyl->dir), 2) - fcyl->radius * fcyl->radius;
	disc = b * b - 4 * a * c;
	if (disc > 0)
	{
		r = (-1 * b - sqrt(disc)) / (2 * a);
		if (r < hit->tnear && r > 0.0001 && fcyl_test(hit, fcyl, r) == 1)
		{
			fcyl->plan = 0;
      *res = r;
			return (1);
		}
		if (hit_fcylbord(fcyl, hit, res, 1))
		{
			fcyl->plan = 1;
			//plane_normale(fcyl->plan1, hit);
		//	*res = r;
			return(1);
		}
		if (hit_fcylbord(fcyl, hit, res, 2))
		{
			fcyl->plan = 2;
		//	*res = r;
			return(1);
		}
		r = (-1 * b + sqrt(disc)) / (2 * a);
		if (r < hit->tnear && r > 0.0001 && fcyl_test(hit, fcyl, r) == 1)
		{
			fcyl->plan = 0;
      *res = r;
			return (1);
		}
	}
	return (0);
}

void		fcylinder_normale(t_fcylinder *cylinder, t_ray *hit)
{
	t_vec3f uv;
//printf("%d\n", cylinder->plan);
	if (cylinder->plan == 1)
		plane_normale(cylinder->plan1, hit);
	//else if (cylinder->plan == 2)
	//{printf("%d\n", cylinder->plan);
	//	plane_normale(cylinder->plan2, hit);
//}
if (cylinder->plan == 0)
	{
		//printf("%d\n", cylinder->plan);
		vec3f_cpy(&hit->nhit, &hit->phit);
		vec3f_sub2(&hit->nhit, &cylinder->base);
		vec3f_cpy(&uv, &cylinder->dir);
		vec3f_mul_unit2(&uv, vec3f_dot(&cylinder->dir, &hit->nhit));
		vec3f_sub2(&hit->nhit, &uv);
	}
}*/

void		fcylindre_print(t_fcylinder *cylinder)
{
	ft_printf("radius: ");
	printf("%g", cylinder->radius); fflush(stdout);
	ft_printf("\ndir:");
	vec3f_print(&cylinder->dir);
}

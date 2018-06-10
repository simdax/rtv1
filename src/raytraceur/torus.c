/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:57:58 by cbesse            #+#    #+#             */
/*   Updated: 2018/06/06 15:57:59 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

static void	tore_def2(t_tore *tore)
{
	tore->center.x = 1;
	tore->center.y = 1;
	tore->center.z = -5;
	tore->prad = 0.5;
  tore->grad = 1;
	tore->dir.x = 0;
	tore->dir.y = 1;
	tore->dir.z = 1;
	tore->dir = v_normalize(tore->dir);
	//tore->dir = v_negate(tore->dir);
}

void		tore_def(t_scene *scene)
{
	int j;

	j = 0;
	scene->list[scene->i].form = (t_tore *)ft_memalloc(sizeof(t_tore));
	tore_def2(scene->list[scene->i].form);
	scene->list[scene->i].color.x = 1;
	scene->list[scene->i].color.y = 0.5;
	scene->list[scene->i].color.z = 0;
	scene->list[scene->i].ks = 0;
	scene->list[scene->i].kt = 0;
	scene->list[scene->i].type = 7;
	scene->list[scene->i].index = scene->i;
	scene->i++;
	while (j < scene->i)
		scene->list[j++].size = scene->i;
}

void			tore_rec(t_ray2 *ray, t_tore *tore, t_record *rec)
{
	double	k;
	t_vecteur	a;
	double	m;

	rec->p = v_add(ray->ori, v_mult(ray->dir, rec->t));
  k =  v_dot(v_less(rec->p, tore->center), tore->dir);
  a = v_less(rec->p, v_mult(tore->dir, k));
  m = sqrt(tore->prad*tore->prad - k * k);
  rec->normal = v_normalize(v_less(rec->p, v_less(a, v_div(v_mult(v_less(tore->center, a), m), tore->grad + m))));
	if (v_dot(ray->dir, tore->dir) > 0)
		v_negate(rec->normal);
		rec->texture.x = 0;
		rec->texture.y = 0;
}

int				hit_tore(t_tore *tore, t_ray2 *ray, double *min_max, \
		t_record *rec)
{
  double m;
  double n;
  double o;
  double p;
  double q;
  double *abcde;
  double *res;
  t_vecteur oc;
  int i;
	double pr;
	double gr;
	int f = 0;
	double	k;
	t_vecteur	a;
	double	mt;
	t_vecteur pt;

	pr = pow(tore->prad,2);
	gr = pow(tore->grad,2);
	//pr = tore->prad;
	//gr = tore->grad;
	//printf("%f, %f, %f\n",ray->dir.x, ray->dir.y, ray->dir.z );
  i = -1;
  abcde = ft_memalloc(sizeof(double) * 5);
  res = ft_memalloc(sizeof(double) * 4);
  m = v_dot(ray->dir, ray->dir);
  oc = v_less(ray->ori, tore->center);
  n = v_dot(ray->dir, oc);
  o = v_dot(oc, oc);
  p = v_dot(ray->dir, tore->dir);
  q = v_dot(oc, tore->dir);
	//printf("m = %f\nn = %f\no = %f\np = %f\nq = %f\n---\n", m,n,o,p,q );
//printf("c.x = %f\nc.y = %f\nc.z = %f\nd.x = %f\nd.y = %f\nd.z = %f\nr = %f\nR = %f\n---------\n",tore->center.x, tore->center.y, tore->center.z, tore->dir.x, tore->dir.y, tore->dir.z, tore->prad, tore->grad);
abcde[0] = pow(m,2);
abcde[1] = 4 * m * n;
abcde[2] = 4 * pow(m,2) + 2 * m * o - 2 * (gr + pr) * m + 4 * gr * pow(p,2);
abcde[3] = 4 * n * o - 4 * (gr + pr) * n + 8 * gr * p * q;
abcde[4] = pow(o,2) - 2 * (gr + pr) * o + 4 * gr * pow(q,2) + pow(gr - pr,2);
	//printf("a = %f\nb = %f\nc = %f\nd = %f\ne = %f\n---\n", abcde[0],abcde[1],abcde[2],abcde[3], abcde[4] );
	if (abcde[0] == 0 && abcde[1] == 0)
	{
		printf("ha\n");
		return(0);
	}
	if (abcde[0] == 0 && abcde[1] != 0)
	{
		printf("ho\n");
		return(0);
	}
	if (abcde[0] != 0)
  	ft_equa4(abcde, res);
	//printf("a = %f\nb = %f\nc = %f\nd = %f\ne = %f\n---\nx0 = %f\nx1 = %f\nx2 = %f\nx2 = %f\n---------\n",abcde[0],abcde[1],abcde[2],abcde[3], abcde[4], res[0], res[1], res[2], res[3]);
  while(++i < 4)
  {
		if (res[i] != DBL_MAX)
		{
			pt = v_add(ray->ori, v_mult(ray->dir, res[i]));
	  	k =  v_dot(v_less(pt, tore->center), tore->dir);
	  	a = v_less(pt, v_mult(tore->dir, k));
	  	mt = tore->prad*tore->prad - k * k;
			//printf("mt = %f\n", mt);
		}
    if(res[i] > 0.001 && res[i] < min_max[1] && mt > 0)
    {
      min_max[1] = res[i];
      rec->t = res[i];
      f = 1;
    }
  }
  if(f == 1)
  {
    tore_rec(ray, tore, rec);
		//printf("t = %f\n",rec->t);
		free(abcde);
		free(res);
    return(1);
  }
	free(abcde);
	free(res);
  return (0);
}

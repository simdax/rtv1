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
	tore->center.x = 0;
	tore->center.y = 0;
	tore->center.z = -2;
	tore->prad = 0.1;
  tore->grad = 0.3;
	tore->dir.x = 0;
	tore->dir.y = 0;
	tore->dir.z = 1;
	tore->dir = v_normalize(tore->dir);
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
	if (v_dot(ray->dir, rec->normal) > 0)
		rec->inside = 1;
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

  i = -1;
  abcde = ft_memalloc(sizeof(double) * 5);
  res = ft_memalloc(sizeof(double) * 4);
  m = v_dot(ray->dir, ray->dir);
  oc = v_less(ray->ori, tore->center);
  n = v_dot(ray->dir, oc);
  o = v_dot(oc, oc);
  p = v_dot(ray->dir, tore->dir);
  q = v_dot(oc, tore->dir);

  abcde[0] = m * m;
  abcde[1] = 4 * m * n;
  abcde[2] = 4 * m * m + 2 * m * o
    - 2 * (tore->grad * tore->grad + tore->prad * tore->prad) * m
    + 4 * tore->grad * tore->grad * p * p;
  abcde[3] = 4 * n * o - 4 * (tore->grad * tore->grad + tore->prad * tore->prad)
   * n + 8 * tore->grad * tore->grad * p * q;
  abcde[4] = o * o - 2 * (tore->grad * tore->grad + tore->prad * tore->prad) * o
  + 4 * tore->grad * tore->grad * q * q
  + pow((tore->grad * tore->grad + tore->prad * tore->prad), 2);
	printf("a = %f\nb = %f\nc = %f\nd = %f\ne = %f\n", abcde[0],abcde[1],abcde[2],abcde[3], abcde[4] );
  ft_equa4(abcde, res);
	printf("x0 = %f\nx1 = %f\nx2 = %f\nx2 = %f\n---------\n", res[0], res[1], res[2], res[3]);
  while(++i < 4)
  {
    if(res[i] > min_max[0] && res[i] < min_max[1] && res[i] != DBL_MAX)
    {
      min_max[1] = res[i];
      rec->t = res[i];
      rec->hit_anything = 1;
    }
  }
  if(rec->hit_anything == 1)
  {
    tore_rec(ray, tore, rec);
		free(abcde);
		free(res);
    return(1);
  }
	free(abcde);
	free(res);
  return (0);
}

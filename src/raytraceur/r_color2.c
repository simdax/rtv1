/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   couleur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:02:00 by cbesse            #+#    #+#             */
/*   Updated: 2018/06/08 21:01:12 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vecteur	r_background(t_ray2 *ray)
{
	t_vecteur	v2;
	t_vecteur	v1;
	t_vecteur	vr;
	double		t;

	v1 = v_set(1.0, 1.0, 1.0);
	v2 = v_set(0.5, 0.7, 1.0);
	t = 0.5 * (ray->dir.y + 1.0);
	vr = v_add(v_mult(v1, (1.0 - t)), v_mult(v2, t));
	return (vr);
}

t_vecteur	diffu_spec(t_vecteur light, t_record *r)
{
	t_vecteur	temp;
	t_vecteur	refrac;
	t_vecteur	diffu;
	double		shade;
	double		phong;

	temp = v_normalize(v_less(light, r->p));
	refrac = v_less(v_mult(r->normal, 2 * v_dot(r->normal, temp)), temp);
	phong = v_dot(refrac, temp);
	shade = v_dot(r->normal, temp);
	shade = shade < 0 ? 0 : shade;
	phong = phong < 0 ? 0 : phong;
	phong = pow(phong, 16);
	diffu.x = r->color.x * (AMBIANT + (1 - AMBIANT) * shade) + phong;
	diffu.y = r->color.y * (AMBIANT + (1 - AMBIANT) * shade) + phong;
	diffu.z = r->color.z * (AMBIANT + (1 - AMBIANT) * shade) + phong;
	return (diffu);
}

t_vecteur	c_shadow(t_vecteur *light, t_record *r, t_vecteur vr, int n_light)
{
	vr = v_add(diffu_spec(light[n_light], &r[0]), vr);
	vr = v_mult(vr, pattern(r));
	vr.x = vr.x > 1 ? 1 : vr.x;
	vr.y = vr.y > 1 ? 1 : vr.y;
	vr.z = vr.z > 1 ? 1 : vr.z;
	return (vr);
}

t_ray2		refraction(t_ray2 *ray, t_record *r)
{
	double		cosi;
	double		eta;
	double		k;
	t_ray2		refrac;
	double		etat;

	etat = IOR;
	cosi = v_dot(r->normal, v_normalize(ray->dir));
	if (cosi < 0)
		cosi = -cosi;
	else
		r->normal = v_negate(r->normal);
	eta = IOR / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	if (k > 0)
		refrac.dir = v_add(v_mult(ray->dir, eta), v_mult(r->normal, eta * \
					cosi - sqrtf(k)));
	else
		refrac.dir = v_set(0, 0, 0);
	refrac.dir = v_normalize(refrac.dir);
	refrac.ori = v_less(r->p, v_mult(r[0].normal, EPSILON));
	return (refrac);
}

float		ft_fresnel(t_ray2 *ray, t_record *r)
{
	double tmp;
	double kr;

	tmp = -v_dot(ray->dir, r[0].normal);
	tmp = pow(1 - tmp, 3);
	kr = 1 * 0.1 + tmp * (1 - 0.1);
	kr = kr > 1 ? 1 : kr;
	return (kr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 15:59:49 by cbesse            #+#    #+#             */
/*   Updated: 2018/03/30 12:19:42 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vecteur	v_add(t_vecteur v1, t_vecteur v2)
{
	t_vecteur	v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vecteur	v_less(t_vecteur v1, t_vecteur v2)
{
	t_vecteur	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

t_vecteur	v_cross(t_vecteur v1, t_vecteur v2)
{
	t_vecteur	v3;

	v3.x = ((v1.y * v2.z) - (v1.z * v2.y));
	v3.y = ((v1.z * v2.x) - (v1.x * v2.z));
	v3.z = ((v1.x * v2.y) - (v1.y * v2.x));
	return (v3);
}

double		v_dot(t_vecteur v1, t_vecteur v2)
{
	double	r;

	r = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (r);
}

double		v_norm(t_vecteur v)
{
	double	norm;

	norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (norm);
}

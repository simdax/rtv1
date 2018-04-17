/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolveQuadratics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:08:22 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/17 17:40:19 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3f.h"

int	resolve_quadratic(t_vec3f equation, float *solution)
{
	float	det;
	float	t1;
	float	t2;

	det = equation.y * equation.y - 4 * equation.x * equation.z;
	if (det < 0)
		return (0);
	det = sqrt(det);
	t1 = (-equation.y + det) / (2 * equation.x);
	t2 = (-equation.y - det) / (2 * equation.x);
	if (t1 < 0 && t2 < 0)
		return (0);
	else if (t2 > 0 && t2 < t1)
		*solution = t2;
	else
		*solution = t1;
	return (1);
}

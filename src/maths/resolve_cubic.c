/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_cubic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:48:11 by cbesse            #+#    #+#             */
/*   Updated: 2018/06/06 14:16:21 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_equ3		ini_equa3(double a, double b, double c, double d)
{
	t_equ3 eq;

	eq.p = c / a - (b * b) / (3 * a * a);
	eq.q = (b / (27 * a)) * ((2 * b * b) / (a * a) - (9 * c) / a) + d / a;
	eq.delta = -(27 * eq.q * eq.q + 4 * eq.p * eq.p * eq.p);
	eq.j = cexp(2 * I * M_PI / 3);
	eq.j2 = cexp(4 * I * M_PI / 3);
	eq.k = 0;
	return (eq);
}

void		ft_equa3_neg(_Complex double *res, t_equ3 eq, double a, double b)
{
	_Complex double	u[3];
	_Complex double	v[3];

	u[0] = sqrt3((-eq.q + sqrt(-eq.delta / 27)) / 2);
	v[0] = sqrt3((-eq.q - sqrt(-eq.delta / 27)) / 2);
	u[1] = eq.j * sqrt3((-eq.q + sqrt(-eq.delta / 27)) / 2);
	v[1] = eq.j * sqrt3((-eq.q - sqrt(-eq.delta / 27)) / 2);
	u[2] = eq.j2 * sqrt3((-eq.q + sqrt(-eq.delta / 27)) / 2);
	v[2] = eq.j2 * sqrt3((-eq.q - sqrt(-eq.delta / 27)) / 2);
	res[0] = u[0] + v[0] - b / (3 * a);
	res[1] = u[1] + v[2] - b / (3 * a);
	res[2] = u[2] + v[1] - b / (3 * a);
}

void		pos_equa_3(_Complex double *res, t_equ3 eq, double a, double b)
{
	res[0] = 2 * sqrt(-eq.p / 3) * cos(acos((3 * eq.q /
				(2 * eq.p)) * sqrt(-3 / eq.p)) / 3) - b / (3 * a);
	res[1] = 2 * sqrt(-eq.p / 3) * cos((acos((3 * eq.q /
				(2 * eq.p)) * sqrt(-3 / eq.p)) + 2 * M_PI) / 3) - b / (3 * a);
	res[2] = 2 * sqrt(-eq.p / 3) * cos((acos((3 * eq.q /
				(2 * eq.p)) * sqrt(-3 / eq.p)) + 4 * M_PI) / 3) - b / (3 * a);
}

void		ft_equa3(double *abcd, _Complex double *res)
{
	t_equ3	eq;

	eq = ini_equa3(abcd[0], abcd[1], abcd[2], abcd[3]);
	if (eq.p == 0 && eq.q == 0)
		res[0] = -abcd[1] / (3 * abcd[0]);
	else if (eq.p == 0 && eq.q != 0)
		res[0] = -eq.q;
	if (eq.delta < 0)
		ft_equa3_neg(res, eq, abcd[0], abcd[1]);
	if (eq.delta == 0)
	{
		res[0] = 2 * sqrt3(-eq.q / 2) - abcd[1] / (3 * abcd[0]);
		res[1] = sqrt3(eq.q / 2) - abcd[1] / (3 * abcd[0]);
		res[2] = res[1];
	}
	if (eq.delta > 0)
		pos_equa_3(res, eq, abcd[0], abcd[1]);
}

double		ft_real(_Complex double *res)
{
	double		y;

	y = DBL_MAX;
	if (cimag(res[0]) == 0)
		y = res[0];
	else if (cimag(res[1]) == 0)
		y = res[1];
	else if (cimag(res[2]) == 0)
		y = res[2];
	else
	{
		res[0] = DBL_MAX;
		res[1] = DBL_MAX;
		res[2] = DBL_MAX;
	}
	return (y);
}

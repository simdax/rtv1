/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_quatric.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:34:07 by cbesse            #+#    #+#             */
/*   Updated: 2018/06/06 15:48:59 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_ini_equa4(t_equ4 *equa, double *abcde)
{
	equa->a[0] = abcde[0] / abcde[0];
	equa->a[1] = abcde[1] / abcde[0];
	equa->a[2] = abcde[2] / abcde[0];
	equa->a[3] = abcde[3] / abcde[0];
	equa->a[4] = abcde[4] / abcde[0];
}

void	ft_equa4_next(t_equ4 *equa, double *abcde, double *res)
{
	ft_equa2(equa, 1, -equa->a0, equa->y + equa->b0);
	equa->x[2] = equa->x[0] - abcde[1] / (4 * abcde[0]);
	equa->x[3] = equa->x[1] - abcde[1] / (4 * abcde[0]);
	ft_equa2(equa, 1, equa->a0, equa->y - equa->b0);
	equa->x[0] = equa->x[0] - abcde[1] / (4 * abcde[0]);
	equa->x[1] = equa->x[1] - abcde[1] / (4 * abcde[0]);
	if (cimag(equa->x[0]) != 0)
		res[0] = DBL_MAX;
	else
		res[0] = creal(equa->x[0]);
	if (cimag(equa->x[1]) != 0)
		res[1] = DBL_MAX;
	else
		res[1] = creal(equa->x[1]);
	if (cimag(equa->x[2]) != 0)
		res[2] = DBL_MAX;
	else
		res[2] = creal(equa->x[2]);
	if (cimag(equa->x[3]) != 0)
		res[3] = DBL_MAX;
	else
		res[3] = creal(equa->x[3]);
}

void	equa4_mid(t_equ4 *equa)
{
	double			*abcd;
	_Complex double	*tmpres;

	abcd = ft_memalloc(sizeof(double) * 4);
	tmpres = ft_memalloc(sizeof(_Complex double) * 3);
	equa->p = -3 * pow(equa->a[1], 2) / (8 * pow(equa->a[0], 2))
		+ equa->a[2] / equa->a[0];
	equa->q = pow(equa->a[1] / 2, 3) / pow(equa->a[0], 3) - (0.5 *
			equa->a[1] * equa->a[2]) / pow(equa->a[0], 2) +
		equa->a[3] / equa->a[0];
	equa->r = -3 * pow((equa->a[1] / 4) / equa->a[0], 4) +
		equa->a[2] * (pow(equa->a[1] / 4, 2) / pow(equa->a[0], 3)) -
		(equa->a[1] * equa->a[3] / 4) / pow(equa->a[0], 2)
		+ equa->a[4] / equa->a[0];
	abcd[0] = 8;
	abcd[1] = -4 * equa->p;
	abcd[2] = -8 * equa->r;
	abcd[3] = 4 * equa->r * equa->p - (equa->q * equa->q);
	ft_equa3(abcd, tmpres);
	equa->y = ft_real(tmpres);
	free(tmpres);
	free(abcd);
}

void	ft_equa4_1(t_equ4 *equa, double *res)
{
	double			*abcd;
	_Complex double	*tmpres;

	tmpres = ft_memalloc(sizeof(_Complex double) * 3);
	abcd = ft_memalloc(sizeof(double) * 4);
	abcd[0] = equa->a[0];
	abcd[1] = equa->a[1];
	abcd[2] = equa->a[2];
	abcd[3] = equa->a[3];
	ft_equa3(abcd, tmpres);
	res[0] = creal(tmpres[0]);
	res[1] = creal(tmpres[1]);
	res[2] = creal(tmpres[2]);
	res[3] = 0;
	free(tmpres);
	free(abcd);
}

void	ft_equa4(double *abcde, double *res)
{
	t_equ4		*eq;

	eq = ft_memalloc(sizeof(t_equ4));
	ft_ini_equa4(eq, abcde);
	if (eq->a[0] == 0)
		ft_equa4_1(eq, res);
	else
	{
		equa4_mid(eq);
		if (eq->y == DBL_MAX)
			return ;
		if (-eq->p + 2 * eq->y > 0)
			eq->a0 = sqrt(-eq->p + 2 * eq->y);
		else
			eq->a0 = I * sqrt(eq->p - 2 * eq->y);
		if (2 * eq->y - eq->p == 0)
			eq->b0 = sqrt(eq->y * eq->y - eq->r);
		else
			eq->b0 = -eq->q / (2 * eq->a0);
		ft_equa4_next(eq, abcde, res);
	}
	free(eq);
}

int main(int ac, char **av)
{
	double *abcde;
	double *res;
ac = 0;
	abcde = ft_memalloc(sizeof(double) * 5);
	res = ft_memalloc(sizeof(double) * 4);
	abcde[0] = ft_atof(av[0]);
	abcde[1] = ft_atof(av[1]);
	abcde[2] = ft_atof(av[2]);
	abcde[3] = ft_atof(av[3]);
	abcde[4] = ft_atof(av[4]);
	ft_equa4(abcde, res);
	printf("a = %f, b = %f, c = %f, d = %f, e = %f\n", abcde[0], abcde[1], abcde[2], abcde[3], abcde[4]);
	printf("x0 = %f\nx1 = %f\nx2 = %f\nx3 = %f\n", res[0], res[1], res[2], res[3]);
}

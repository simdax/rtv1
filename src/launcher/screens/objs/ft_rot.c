/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:16:19 by alerandy          #+#    #+#             */
/*   Updated: 2018/06/08 10:44:38 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

void	ft_rot_z(double *x, double *y, double teta)
{
//	double	teta;
	double	xtmp;

	xtmp = *x;
//	teta = a * ((2 * M_PI) / 360);
	*x = (xtmp * cos(teta)) - (*y * sin(teta));
	*y = (xtmp * sin(teta)) + (*y * cos(teta));
}

void	ft_rot_x(double *y, double *z, double teta)
{
//	double	teta;
	double	ztmp;

	ztmp = *z;
//	teta = a * ((2 * M_PI) / 360);
	*z = (sin(teta) * *y) + (cos(teta) * *z);
	*y = (cos(teta) * *y) - (sin(teta) * ztmp);
}

void	ft_rot_y(double *x, double *z, double teta)
{
//	double	teta;
	double	ztmp;

	ztmp = *z;
//	teta = a * ((2 * M_PI) / 360);
	*z = -(sin(teta) * *x) + (cos(teta) * *z);
	*x = (cos(teta) * *x) + (sin(teta) * ztmp);
}

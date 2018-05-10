/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:38:01 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/09 18:07:17 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3f.h"

void	vec3f_cpy(t_vec3f *a, t_vec3f *b)
{
	vec3f_set(a, b->x, b->y, b->z);
}

void	vec3f_normalize2(t_vec3f *a)
{
	vec3f_mul_unit2(a, 1 / length(a));
}

void	vec3f_set(t_vec3f *instance, double x, double y, double z)
{
	instance->x = x;
	instance->y = y;
	instance->z = z;
}

t_vec3f	*vec3f_new(double x, double y, double z)
{
	t_vec3f		*instance;

	instance = malloc(sizeof(t_vec3f));
	vec3f_set(instance, x, y, z);
	return (instance);
}

void	vec3f_print(t_vec3f *a)
{
		ft_printf("[");
		ft_putfloat(a->x);
		ft_printf(", ");
		ft_putfloat(a->y);
		ft_printf(", ");
		ft_putfloat(a->z);
		ft_printf("]\n");
//	printf("[%g, %g, %g]\n", a->x, a->y, a->z);
}

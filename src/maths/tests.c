/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:08:53 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/23 12:05:13 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3f.h"
#include "resolvequadratics.h"

int	main(void)
{
	t_vec3f	equation;
	double	solution;

	equation = (t_vec3f){1, -3, -4};
	solution = 0;
	if (resolve_quadratic(equation, &solution))
		printf("%g", solution);
	else
		printf("pas de solution");
}

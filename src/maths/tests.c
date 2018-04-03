/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:08:53 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/03 16:50:21 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(void)
{
	t_vec3f	equation;
	float	solution;

	equation = (t_vec3f){1, -3, -4};
	solution = 0;
	if (resolveQuadratic(equation, &solution))
		printf("%g", solution);
	else
		printf("pas de solution");
}

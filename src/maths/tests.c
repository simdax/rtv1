/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:08:53 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/03 16:35:27 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main()
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

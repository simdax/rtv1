/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:08:53 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/03 12:09:03 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main()
{
	t_vec3f	equation = (t_vec3f){1, -3, -4};
	float		solution = 0;

	if(resolveQuadratic(equation, &solution))
		printf("%g", solution);
	else
		printf("pas de solution");
}

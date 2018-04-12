/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 12:20:31 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/01 16:17:44 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATHS_H
# define FT_MATHS_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft.h"

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

float			ft_sqrt(float nb);
float			ft_div(float a, float b);
float			ft_root(float nb, float root);
float			ft_pow2(float nb, float pow);
int				ft_pow(int base, int power);
double			ft_pow3(double base, double power);
int				is_prime(int nb);
void			prime_factors(int nb);
int				gcd(int a, int b);

#endif

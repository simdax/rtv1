/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 14:18:40 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/09 18:10:35 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					calculate_size(long l, long *size)
{
	*size = 1;
	while (*size <= l)
		*size = *size * 10;
	*size = *size / 10;
}

void					write_float(long l, long size)
{
	while (size > 1)
	{
		ft_putchar((l / size) + '0');
		l = l % size;
		size = size / 10;
	}
	ft_putchar((l % 10) + '0');
}

void					negative(float *f)
{
	if (*f < 0)
	{
		ft_putchar('-');
		*f = -(*f);
	}
}

void					ft_putfloat(float f)
{
	long				size;
	long				size_tmp;
	long				tmp;
	unsigned long		tmp2;

	negative(&f);
	tmp = f;
	calculate_size(tmp, &size);
	size_tmp = 2;
	write_float(tmp, size);
	tmp2 = (unsigned long)(f * 1000);
	ft_putchar('.');
	if (tmp2 != 0)
	{
		calculate_size(tmp2, &size);
		while (size_tmp >= 1)
		{
			tmp2 = tmp2 % size;
			size = size / 10;
			size_tmp = size_tmp / 10;
		}
		write_float(tmp2, size);
	}
}

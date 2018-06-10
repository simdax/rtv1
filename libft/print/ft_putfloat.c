/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 14:18:40 by acourtin          #+#    #+#             */
/*   Updated: 2018/06/10 18:02:26 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putfloat_fd(float f, int precis, int fd)
{
	int		a;
	int		i;

	a = 10;
	(int)f == 0 && f < 0 ? ft_putchar_fd('-', fd) : 0;
	ft_putnbr_fd((int)f, fd);
	ft_putchar_fd('.', fd);
	f < 0 ? f = -f : 0;
	f -= (int)f;
	i = 0;
	while (++i < precis)
		a *= 10;
	f *= a;
	ft_putnbr_fd((int)f, fd);
}

void		ft_putfloat(float f, int precis)
{
	int		a;
	int		i;

	a = 10;
	(int)f == 0 && f < 0 ? ft_putchar_fd('-', 0) : 0;
	ft_putnbr_fd((int)f, 0);
	ft_putchar_fd('.', 0);
	f < 0 ? f = -f : 0;
	f -= (int)f;
	i = 0;
	while (++i < precis)
		a *= 10;
	f *= a;
	ft_putnbr_fd((int)f, 0);
}

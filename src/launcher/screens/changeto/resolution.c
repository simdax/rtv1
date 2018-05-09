/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:02:07 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/09 14:38:04 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		*reset_resolution(void *param)
{
	t_launch	*res;

	res = param;
	res->width = 0;
	res->height = 0;
	ft_putendl("Resolution par defaut");
	return (NULL);
}

void		*change_resolution(void *param)
{
	t_launch	*res;

	res = param;
	res->width = 800;
	res->height = 600;
	ft_putstr("Nouvelle Resolution : ");
	ft_putnbr(res->width);
	ft_putstr(" X ");
	ft_putnbr(res->height);
	ft_putchar('\n');
	return (NULL);
}

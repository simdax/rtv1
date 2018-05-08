/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:14:56 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/08 11:30:22 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

static void		destr(const int c, int *r, int *g, int *b)
{
	*r = (c / (256 * 256)) % 256;
	*g = (c / 256) % 256;
	*b = c % 256;
}

static int		restr(const int r, const int g, const int b)
{
	return ((r * 256 * 256) + (g * 256) + b);
}

void			change_colors(t_render_opts *opts)
{
	int			i;
	int			j;
	t_clr		c;

	j = 0;
	while (j < opts->height)
	{
		i = 0;
		while (i < opts->width)
		{
			destr(opts->pixels[(int)(i + (j * opts->width))], &c.r, &c.g, &c.b);
			opts->pixels[(int)(i + (j * opts->width))] = restr(c.r, c.g, c.b);
			i++;
		}
		j++;
	}
}

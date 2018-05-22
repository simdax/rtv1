/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 10:47:56 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/22 10:39:06 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "colors.h"

void			destr(const int cl, t_clr *c)
{
	*c = (t_clr){((int)(cl / 256) / 256),
		((int)(cl / 256)) & 0x0000FF, cl & 0x0000FF};
}

void			destr2(const int cl, t_clr *c, int *ok)
{
	*c = (t_clr){((int)(cl / 256) / 256),
		((int)(cl / 256)) & 0x0000FF, cl & 0x0000FF};
	*ok = 1;
}

int				restr(int r, int g, int b)
{
	r = r > 255 ? 255 : r;
	g = g > 255 ? 255 : g;
	b = b > 255 ? 255 : b;
	r = r < 0 ? 0 : r;
	g = g < 0 ? 0 : g;
	b = b < 0 ? 0 : b;
	return ((r * 256 * 256) + (g * 256) + b);
}

float			determine_luma(t_clr *c)
{
	return (0.299 * c->r + 0.587 * c->g + 0.114 * c->b);
}

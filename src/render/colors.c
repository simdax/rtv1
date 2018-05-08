/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:14:56 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/08 13:10:12 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

static void		destr(const int cl, t_clr *c, t_clr *t)
{
	c->r = (cl / (256 * 256)) % 256;
	c->g = (cl / 256) % 256;
	c->b = cl % 256;
	t->r = (cl / (256 * 256)) % 256;
	t->g = (cl / 256) % 256;
	t->b = cl % 256;
}

static int		restr(const int r, const int g, const int b)
{
	return ((r * 256 * 256) + (g * 256) + b);
}

void			apply_filter(t_clr *t, t_clr *c, t_cfilter f)
{
	if (f == SEPIA)
	{
		t->r = (c->r * .393) + (c->g * .769) + (c->b * .189);
		t->g = (c->r * .349) + (c->g * .686) + (c->b * .168);
		t->b = (c->r * .272) + (c->g * .534) + (c->b * .131);
	}
}

void			change_colors(t_render_opts *opts, t_cfilter f)
{
	int			i;
	int			j;
	t_clr		c;
	t_clr		t;

	j = -1;
	while (++j < opts->height)
	{
		i = -1;
		while (++i < opts->width)
		{
			destr(opts->pixels[(int)(i + (j * opts->width))], &c, &t);
			apply_filter(&t, &c, f);
			t.r > 255 ? t.r = 255 : 1;
			t.g > 255 ? t.g = 255 : 1;
			t.b > 255 ? t.b = 255 : 1;
			opts->pixels[(int)(i + (j * opts->width))] = restr(t.r, t.g, t.b);
		}
	}
}

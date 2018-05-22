/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cellshading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:51:38 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/22 17:00:45 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "colors.h"

static void		apply_cellshading(t_mclr *c, t_render_opts *opts, int i)
{
	t_lumas			l;

	get_lumas(c, opts, i);
	l.luma_min = MIN(c->lce, MIN(MIN(c->ldn, c->lup), MIN(c->lle, c->lri)));
	l.luma_max = MAX(c->lce, MAX(MAX(c->ldn, c->lup), MAX(c->lle, c->lri)));
	l.luma_range = l.luma_max - l.luma_min;
	if (l.luma_range < MAX(CELL_THRESHOLD_MIN, l.luma_max * CELL_THRESHOLD_MAX))
	{
		c->res.r = c->ce.r;
		c->res.g = c->ce.g;
		c->res.b = c->ce.b;
	}
	else
		c->res = (t_clr){0, 0, 0};
}

void			ready_cellshading(t_render_opts *opts)
{
	int			i;
	t_mclr		c;

	i = -1;
	while (++i < opts->width * opts->height)
	{
		destr(opts->pixels[i], &c.ce);
		if (i % (int)opts->width == opts->width - 1 || i < opts->width || \
			i % (int)opts->width == 0 || \
			i / (int)opts->width == (int)opts->height - 1)
			c.res = (t_clr){c.ce.r, c.ce.g, c.ce.b};
		else
			apply_cellshading(&c, opts, i);
		opts->rended[i] = restr(c.res.r, c.res.g, c.res.b);
	}
}

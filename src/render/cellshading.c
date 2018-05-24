/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cellshading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:51:38 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/24 11:44:19 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "colors.h"

static int		cartoonize(int color)
{
	int		power;
	int		res;

	power = (color / 100) + 3;
	res = (color % 155) * power;
	res = res > 255 ? 255 : res;
	res = res < 0 ? 0 : res;
	return (res);
}

static void		apply_cellshading(t_mclr *c, t_render_opts *opts, int i)
{
	t_lumas			l;

	get_lumas(c, opts, i);
	l.luma_min = MIN(c->lce, MIN(MIN(c->ldn, c->lup), MIN(c->lle, c->lri)));
	l.luma_max = MAX(c->lce, MAX(MAX(c->ldn, c->lup), MAX(c->lle, c->lri)));
	l.luma_range = l.luma_max - l.luma_min;
	if (l.luma_range < MAX(CELL_THRESHOLD_MIN, l.luma_max * CELL_THRESHOLD_MAX))
		opts->rended[i] = restr(cartoonize(c->ce.r), cartoonize(c->ce.g), \
			cartoonize(c->ce.b));
	else
	{
		opts->rended[i] = 0;
		if (c->okup)
			opts->rended[(int)(i - opts->width)] = 0;
		if (c->okdn)
			opts->rended[(int)(i + opts->width)] = 0;
		if (c->okle)
			opts->rended[i - 1] = 0;
		if (c->okri)
			opts->rended[i + 1] = 0;
	}
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
			opts->rended[i] = restr(c.ce.r, c.ce.g, c.ce.b);
		else
			apply_cellshading(&c, opts, i);
	}
}

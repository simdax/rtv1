/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:14:56 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/22 13:51:54 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "colors.h"

static void		apply_filter(t_clr *t, t_clr *c, t_cfilter f)
{
	if (f == SEPIA)
		*t = (t_clr){
			(c->r * .393) + (c->g * .769) + (c->b * .189),
			(c->r * .349) + (c->g * .686) + (c->b * .168),
			(c->r * .272) + (c->g * .534) + (c->b * .131)};
	else if (f == GRAYSCALE)
	{
		*t = (t_clr){
			(c->r + c->g + c->b) / 3,
			(c->r + c->g + c->b) / 3,
			(c->r + c->g + c->b) / 3};
		t->r > 80 ? t->r *= 1.5 : 1;
		t->g > 80 ? t->g *= 1.5 : 1;
		t->b > 80 ? t->b *= 1.5 : 1;
	}
	else if (f == NEGATIVE)
		*t = (t_clr){
			255 - c->r,
			255 - c->g,
			255 - c->b};
}

static void		get_lumas(t_mclr *c, t_render_opts *opts, int i)
{
	c->lce = determine_luma(&c->ce);
	if (opts->pixels[(int)(i - opts->width)])
		destr2(opts->pixels[(int)(i - opts->width)], &c->up, &c->okup, &c->lup);
	else
		c->okup = 0;
	if (opts->pixels[(int)(i + opts->width)])
		destr2(opts->pixels[(int)(i + opts->width)], &c->dn, &c->okdn, &c->ldn);
	else
		c->okdn = 0;
	if (opts->pixels[i - 1])
		destr2(opts->pixels[i - 1], &c->le, &c->okle, &c->lle);
	else
		c->okle = 0;
	if (opts->pixels[i + 1])
		destr2(opts->pixels[i + 1], &c->ri, &c->okri, &c->lri);
	else
		c->okri = 0;
	get_lumas2(c, opts, i);
}

static void		apply_fxaa(t_mclr *c, t_render_opts *opts, int i)
{
	t_lumas			l;

	get_lumas(c, opts, i);
	l.luma_min = MIN(c->lce, MIN(MIN(c->ldn, c->lup), MIN(c->lle, c->lri)));
	l.luma_max = MAX(c->lce, MAX(MAX(c->ldn, c->lup), MAX(c->lle, c->lri)));
	l.luma_range = l.luma_max - l.luma_min;
	if (l.luma_range < MAX(EDGE_THRESHOLD_MIN, l.luma_max * EDGE_THRESHOLD_MAX))
	{
		c->res.r = c->ce.r;
		c->res.g = c->ce.g;
		c->res.b = c->ce.b;
	}
	else
		calculate_fxaa(&l, c);
}

static void		ready_fxaa(t_render_opts *opts)
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
			apply_fxaa(&c, opts, i);
		opts->rended[i] = restr(c.res.r, c.res.g, c.res.b);
	}
}

void			change_colors(t_render_opts *opts, t_cfilter f)
{
	int			i;
	int			j;
	t_clr		c;
	t_clr		t;

	if (f == NONE)
		ft_memcpy(opts->rended, opts->pixels, sizeof(int) * (opts->width \
					* opts->height));
	else if (f == FXAA)
		ready_fxaa(opts);
	else
	{
		i = -1;
		while (++i < opts->height * opts->width)
		{
			destr(opts->pixels[i], &c);
			destr(opts->pixels[i], &t);
			apply_filter(&t, &c, f);
			opts->rended[i] = restr(t.r, t.g, t.b);
		}
	}
}

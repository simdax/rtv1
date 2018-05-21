/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:14:56 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/21 15:06:51 by acourtin         ###   ########.fr       */
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

static void		mix_pixels(t_mclr *c, t_render_opts *opts, int i)
{
	if (opts->pixels[(int)(i - opts->width)])
		destr2(opts->pixels[(int)(i - opts->width)], &c->up, &c->okup);
	else
		c->okup = 0;
	if (opts->pixels[(int)(i + opts->width)])
		destr2(opts->pixels[(int)(i + opts->width)], &c->dn, &c->okdn);
	else
		c->okdn = 0;
	if (opts->pixels[i - 1])
		destr2(opts->pixels[i - 1], &c->le, &c->okle);
	else
		c->okle = 0;
	if (opts->pixels[i + 1])
		destr2(opts->pixels[i + 1], &c->ri, &c->okri);
	else
		c->okri = 0;
	c->res.r = (c->ce.r + c->up.r * c->okup + c->dn.r * c->okdn + c->le.r \
		* c->okle + c->ri.r * c->okri) / 5;
	c->res.g = (c->ce.g + c->up.g * c->okup + c->dn.g * c->okdn + c->le.g \
		* c->okle + c->ri.g * c->okri) / 5;
	c->res.b = (c->ce.b + c->up.b * c->okup + c->dn.b * c->okdn + c->le.b \
		* c->okle + c->ri.b * c->okri) / 5;
}

static void		apply_fxaa(t_render_opts *opts)
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
			mix_pixels(&c, opts, i);
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
		apply_fxaa(opts);
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

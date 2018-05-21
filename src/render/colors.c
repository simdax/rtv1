/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:14:56 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/21 10:14:25 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "colors.h"

static void		destr(const int cl, t_clr *c)
{
	*c = (t_clr){(cl / (256 * 256)) % 256, (cl / (256 * 256)) % 256, cl % 256};
}

static int		restr(int r, int g, int b)
{
	r > 255 ? r = 255 : 1;
	g > 255 ? g = 255 : 1;
	b > 255 ? b = 255 : 1;
	r < -255 ? r = -255 : 1;
	g < -255 ? g = -255 : 1;
	b < -255 ? b = -255 : 1;
	return ((r * 256 * 256) + (g * 256) + b);
}

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
	{
		*t = (t_clr){
			c->r * -1,
			c->g * -1,
			c->b * -1};
		t->r == 0 ? t->r = 255 : 1;
		t->g == 0 ? t->g = 255 : 1;
		t->b == 0 ? t->b = 255 : 1;
	}
}

static void		apply_fxaa(t_render_opts *opts)
{
	int			i;
	t_mclr		c;

	i = -1;
	while (++i < opts->width * opts->height)
	{
		destr(opts->pixels[i], &c.ce);
		if (c.ce.r <= 5 && c.ce.g <= 5 && c.ce.b <= 5)
			c.res = (t_clr){c.ce.r, c.ce.g, c.ce.b};
		else
		{
			if (opts->pixels[(int)(i - opts->width)])
				destr(opts->pixels[(int)(i - opts->width)], &c.up);
			if (opts->pixels[(int)(i + opts->width)])
				destr(opts->pixels[(int)(i + opts->width)], &c.dn);
			if (opts->pixels[i - 1])
				destr(opts->pixels[i - 1], &c.le);
			if (opts->pixels[i + 1])
				destr(opts->pixels[i + 1], &c.ri);
			c.res.r = (c.ce.r + c.up.r + c.dn.r + c.le.r + c.ri.r) / 5;
			c.res.g = (c.ce.g + c.up.g + c.dn.g + c.le.g + c.ri.g) / 5;
			c.res.b = (c.ce.b + c.up.b + c.dn.b + c.le.b + c.ri.b) / 5;
		}
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

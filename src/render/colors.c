/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:14:56 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/08 14:44:06 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

static void		destr(const int cl, t_clr *c, t_clr *t)
{
	*c = (t_clr){(cl / (256 * 256)) % 256, (cl / (256 * 256)) % 256, cl % 256};
	*t = (t_clr){(cl / (256 * 256)) % 256, (cl / (256 * 256)) % 256, cl % 256};
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
		*t = (t_clr){
			(c->r + c->g + c->b) / 3,
			(c->r + c->g + c->b) / 3,
			(c->r + c->g + c->b) / 3};
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

void			change_colors(t_render_opts *opts, t_cfilter f)
{
	int			i;
	int			j;
	t_clr		c;
	t_clr		t;

	if (f == NONE)
		return ;
	j = -1;
	while (++j < opts->height)
	{
		i = -1;
		while (++i < opts->width)
		{
			destr(opts->pixels[(int)(i + (j * opts->width))], &c, &t);
			apply_filter(&t, &c, f);
			opts->pixels[(int)(i + (j * opts->width))] = restr(t.r, t.g, t.b);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fxaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:42:15 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/22 13:52:30 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "colors.h"

void			get_lumas2(t_mclr *c, t_render_opts *opts, int i)
{
	if (opts->pixels[(int)(i - opts->width - 1)])
		destr2(opts->pixels[(int)(i - opts->width - 1)], &c->ctmp, &c->itmp, \
			&c->lul);
	if (opts->pixels[(int)(i - opts->width + 1)])
		destr2(opts->pixels[(int)(i - opts->width + 1)], &c->ctmp, &c->itmp, \
			&c->lur);
	if (opts->pixels[(int)(i + opts->width - 1)])
		destr2(opts->pixels[(int)(i + opts->width - 1)], &c->ctmp, &c->itmp, \
			&c->ldl);
	if (opts->pixels[(int)(i + opts->width + 1)])
		destr2(opts->pixels[(int)(i + opts->width + 1)], &c->ctmp, &c->itmp, \
			&c->ldr);
}

void			calculate_fxaa(t_lumas *l, t_mclr *c)
{
	l->luma_downup = c->ldn + c->lup;
	l->luma_leftright = c->lle + c->lri;
	l->luma_leftcorners = c->ldl + c->lul;
	l->luma_downcorners = c->ldl + c->ldr;
	l->luma_rightcorners = c->ldr + c->lur;
	l->luma_upcorners = c->lur + c->lul;
	l->edge_horizontal = ABS(-2.0 * c->lle + l->luma_leftcorners) + \
		ABS(-2.0 * c->lce + l->luma_downup) * 2.0 + \
		ABS(-2.0 * c->lri + l->luma_rightcorners);
	l->edge_vertical = ABS(-2.0 * c->lup + l->luma_upcorners) + \
		ABS(-2.0 * c->lce + l->luma_leftright) * 2.0 + \
		ABS(-2.0 * c->ldn + l->luma_downcorners);
	if (l->edge_horizontal >= l->edge_vertical)
	{
		c->res.r = (c->ce.r + c->up.r * c->okup + c->dn.r * c->okdn) / 3;
		c->res.g = (c->ce.g + c->up.g * c->okup + c->dn.g * c->okdn) / 3;
		c->res.b = (c->ce.b + c->up.b * c->okup + c->dn.b * c->okdn) / 3;
	}
	else
	{
		c->res.r = (c->ce.r + c->le.r * c->okle + c->ri.r * c->okri) / 3;
		c->res.g = (c->ce.g + c->le.g * c->okle + c->ri.g * c->okri) / 3;
		c->res.b = (c->ce.b + c->le.b * c->okle + c->ri.b * c->okri) / 3;
	}
}

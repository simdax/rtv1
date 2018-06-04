/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_interact.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 18:51:52 by alerandy          #+#    #+#             */
/*   Updated: 2018/06/04 17:11:23 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		obj_key(t_render_opts *opts, t_sdl *sdl, t_obj *obj)
{
	if (sdl->event->key.keysym.sym == 27)
		sdl->quit = 1;
	else
		each_control(opts, sdl, obj);
	SDL_Delay(100);
	sdl->quit == 0 ? sdl->is_rendering = 0 : 0;
}

static void	init_obj(t_rt *opts)
{
	int			x;
	int			y;
	t_vec3f		ray;
	t_ray		tmp;

	SDL_GetMouseState(&x, &y);
	ray = create_ray(x, y, opts->thr->opts);
	ray = matrix_mul(opts->thr->opts->matrix, ray);
	opts->selected ? opts->selected->surface_color.x -= 255 : 0;
	opts->selected ? opts->thr->opts->it = ITRES : 0;
	if (opts->thr->sdl)
	{
		tmp.tnear = INFINITY;
		tmp.rayorig = opts->thr->opts->camorig;
		tmp.raydir = ray;
		tmp.obj_index = -1;
		opts->thr->sobj = ft_objtouche(*opts->thr->opts->spheres, &tmp);
		opts->selected = opts->thr->sobj != opts->selected ? \
						opts->thr->sobj : 0;
	}
}

void		getobj(t_rt *opts)
{
	if (opts->thr->sdl && opts->thr->sdl->event->type == SDL_MOUSEBUTTONDOWN &&\
			opts->thr->sdl->id == (int)SDL_GetWindowID(SDL_GetMouseFocus()) \
			&& opts->thr->opts->it == 0)
	{
		init_obj(opts);
		if (opts->selected)
		{
			opts->selected->surface_color.x += 255;
			opts->thr->opts->it = ITRES;
		}
		else if (opts->thr->sobj)
			opts->thr->sobj = 0;
	}
}

void		load_sdl(t_launch *launcher, t_ttf *load, t_texture **txtr)
{
	SDL_Rect		render_quad;
	t_txt_renderer	t;

	render_quad = (SDL_Rect){350, 350, 51, 51};
	t = (t_txt_renderer){400, 400, NULL, 0, NULL};
	t.angle += 45;
	SDL_Delay(150);
	SDL_RenderFillRect(launcher->render, &(launcher->img));
	SDL_RenderCopy(launcher->render, load->texture, NULL, &(load->dstrect));
	SDL_RenderCopyEx(launcher->render, txtr[0]->texture, NULL, \
			&(render_quad), t.angle, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(launcher->render);
}

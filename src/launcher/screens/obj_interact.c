/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_interact.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 18:51:52 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/18 04:23:03 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		obj_key(t_render_opts *opts, t_sdl *sdl, t_obj *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_DOWN)
		obj->position.y -= 1;
	else if (sdl->event->key.keysym.sym == SDLK_UP)
		obj->position.y += 1;
	else if (sdl->event->key.keysym.sym == SDLK_RIGHT)
		obj->position.x += 1;
	else if (sdl->event->key.keysym.sym == SDLK_LEFT)
		obj->position.x -= 1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_5)
		obj->position.z -= 1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_8)
		obj->position.z += 1;
	else if (sdl->event->key.keysym.sym == 27)
		sdl->quit = 1;
	else
		controla(opts, sdl, obj);
	sdl->quit == 0 ? sdl->is_rendering = 0 : 0;
}

static void	init_obj(t_launch *launch, t_rt *opts)
{
	int			x;
	int			y;
	t_vec3f		ray;
	t_vec3f		color;

	SDL_GetMouseState(&x, &y);
	ray = create_ray(x, y, opts->thr->opts);
	ray = matrix_mul(opts->thr->opts->matrix, ray);
	opts->selected ? opts->selected->surface_color.x -= 255 : 0;
	opts->selected ? opts->thr->opts->it = ITRES : 0;
	if (opts->thr->sdl)
	{
		opts->thr->sobj = trace(&((t_ray){INFINITY, opts->thr->opts->camorig, \
					ray, -1}), *opts->thr->opts->spheres, 0, &color);
		opts->selected = opts->thr->sobj != opts->selected ? \
						opts->thr->sobj : 0;
	}
}

void		getobj(t_launch *launch, t_rt *opts)
{
	if (opts->thr->sdl && opts->thr->sdl->event->type == SDL_MOUSEBUTTONDOWN &&\
			opts->thr->sdl->id == (int)SDL_GetWindowID(SDL_GetMouseFocus()) \
			&& opts->thr->opts->it == 0)
	{
		init_obj(launch, opts);
		if (opts->selected)
		{
			opts->selected->surface_color.x += 255;
			opts->thr->opts->it = ITRES;
		}
		else if (opts->thr->sobj)
			opts->thr->sobj = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <scornaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:08:44 by scornaz           #+#    #+#             */
/*   Updated: 2018/06/05 16:02:28 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "interface.h"
#include "colors.h"

static void	change_scene(t_render_opts *opts)
{
	ft_printf("objects:\n");
	while (**opts->spheres)
	{
		ft_printf("%s @ %p\n", (**opts->spheres)->tag, **opts->spheres);
		++(*opts->spheres);
	}
	ft_printf("///\n");
	++(*opts->spheres);
	if (!**opts->spheres)
	{
		while (*opts->spheres != opts->orig)
			--(*opts->spheres);
	}
}

static void	key_event(t_render_opts *opts, t_sdl *sdl)
{
	if (sdl->event->key.keysym.sym == SDLK_DOWN)
		opts->camorig.z += 1;
	else if (sdl->event->key.keysym.sym == SDLK_UP)
		opts->camorig.z -= 1;
	else if (sdl->event->key.keysym.sym == SDLK_RIGHT)
		opts->camorig.x += 1;
	else if (sdl->event->key.keysym.sym == SDLK_LEFT)
		opts->camorig.x -= 1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_8)
		opts->camdir.y += 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_5)
		opts->camdir.y -= 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_6)
		opts->camdir.x += 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_4)
		opts->camdir.x -= 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_a)
		change_scene(opts);
	else if (sdl->event->key.keysym.sym == SDLK_s)
		snap_screen(opts, sdl);
	sdl->event->key.keysym.sym == 27 ? sdl->quit = 1 : 0;
	while ((sdl->event->key.keysym.sym == 27 || sdl->event->key.keysym.sym == \
				SDLK_a || sdl->event->key.keysym.sym == SDLK_s) \
				&& sdl->event->type == SDL_KEYDOWN)
		;
}

static void	event_loop(t_render_opts *opts, t_sdl *sdl, t_thrprm *prm)
{
	int		id;

	id = (int)SDL_GetWindowID(SDL_GetKeyboardFocus());
	SDL_StopTextInput();
	if (sdl->event->key.keysym.sym == SDLK_q && sdl->event->type == SDL_KEYDOWN)
		while (sdl->event->type == SDL_KEYDOWN)
			sdl->quit = 1;
	else if (sdl->event->type == SDL_KEYDOWN && sdl->id == id)
	{
		if (sdl->event->key.keysym.sym != SDLK_s)
			opts->it = ITRES;
		if (prm->sobj)
			obj_key(opts, sdl, prm->sobj);
		else
			key_event(opts, sdl);
	}
	else if (sdl->event->type == SDL_WINDOWEVENT && sdl->id == id)
		if (sdl->event->window.event == SDL_WINDOWEVENT_RESIZED || \
				sdl->event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			changing_res(opts, sdl);
}

static void	events(t_sdl *sdl, t_render_opts *opts, t_thrprm *param)
{
	while (!sdl->quit)
	{
		if (opts->it > 1)
		{
			render(opts) ? 0 : (opts->it += ITSPEED);
			sdl->is_rendering = 0;
			opts->it = opts->it - ITSPEED > 0 ? opts->it - ITSPEED : 1;
		}
		else if (opts->it == 1)
		{
			render_wait(sdl, opts);
			sdl->is_rendering = 0;
			opts->it = 0;
		}
		if (sdl->is_rendering == 0)
			change_colors(opts, sdl->filter);
		sdl->is_rendering = 1;
		SDL_UpdateTexture(sdl->texture, NULL, opts->rended,
							opts->width * sizeof(int));
		event_loop(opts, sdl, param);
		SDL_RenderClear(sdl->renderer);
		SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);
	}
}

void		init_sdl(t_render_opts *opts, t_thrprm *param)
{
	t_sdl		sdl;

	sdl = (t_sdl){NULL, 0, 0, 0, 0, param->event, 0, NONE};
	opts->scname = param->scn;
	param->opts = opts;
	param->sdl = &sdl;
	while (!sdl.window)
		;
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1, 0);
	sdl.texture = SDL_CreateTexture(sdl.renderer,
									SDL_PIXELFORMAT_RGB888,
									SDL_TEXTUREACCESS_STATIC,
									opts->width, opts->height);
	sdl.id = SDL_GetWindowID(sdl.window);
	sdl.event = param->event;
	change_colors(opts, sdl.filter);
	sdl.is_rendering = 1;
	opts->it = 0;
	param->opts = opts;
	events(&sdl, opts, param);
	SDL_DestroyTexture(sdl.texture);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.window);
}

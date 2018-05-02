/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:08:44 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/02 15:52:27 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	event_loop(t_render_opts *opts, t_sdl *sdl)
{
	if (sdl->event->key.keysym.sym == SDLK_q && sdl->event->type == SDL_KEYDOWN)
		sdl->quit = 1;
	else if (sdl->event->type == SDL_KEYDOWN && \
			sdl->id == SDL_GetWindowID(SDL_GetKeyboardFocus()))
	{
		if (sdl->event->key.keysym.sym == SDLK_DOWN)
			opts->camorig.z += 1;
		else if (sdl->event->key.keysym.sym == SDLK_UP)
			opts->camorig.z -= 1;
		else if (sdl->event->key.keysym.sym == SDLK_RIGHT)
			opts->camorig.x += 1;
		else if (sdl->event->key.keysym.sym == SDLK_LEFT)
			opts->camorig.x -= 1;
		else if (sdl->event->key.keysym.sym == SDLK_KP_0)
			opts->camdir.y += 0.1;
		else if (sdl->event->key.keysym.sym == SDLK_KP_1)
			opts->camdir.y -= 0.1;
		else if (sdl->event->key.keysym.sym == SDLK_KP_2)
			opts->camdir.x += 0.1;
		else if (sdl->event->key.keysym.sym == SDLK_KP_3)
			opts->camdir.x -= 0.1;
		sdl->event->key.keysym.sym == 27 ? sdl->quit = 1 : 0;
		render(opts);
	}
}

static void	events(t_sdl *sdl, t_render_opts *opts)
{
	while (!sdl->quit)
	{
		SDL_UpdateTexture(sdl->texture, NULL, opts->pixels,
							opts->width * sizeof(int));
		event_loop(opts, sdl);
		SDL_RenderClear(sdl->renderer);
		SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);
	}
}

void		init_sdl(t_render_opts *opts, SDL_Event *event)
{
	t_sdl		sdl;

	sdl = (t_sdl){
		SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED, opts->width, opts->height, 0),
		0, 0, 0
	};
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1, 0);
	sdl.texture = SDL_CreateTexture(sdl.renderer,
									SDL_PIXELFORMAT_RGB888,
									SDL_TEXTUREACCESS_STATIC,
									opts->width, opts->height);
	sdl.id = SDL_GetWindowID(sdl.window);
	sdl.event = event;
	events(&sdl, opts);
	SDL_DestroyTexture(sdl.texture);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.window);
}

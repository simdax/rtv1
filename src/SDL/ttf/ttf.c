/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 12:29:11 by acourtin          #+#    #+#             */
/*   Updated: 2018/04/05 15:53:51 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ttf.h"

static void		ttf_init(t_ttf *t)
{
	t->quit = 0;
	t->texw = 0;
	t->texh = 0;
	t->window = SDL_CreateWindow("SDL_ttf in SDL2", SDL_WINDOWPOS_UNDEFINED, \
			SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	t->renderer = SDL_CreateRenderer(t->window, -1, 0);
	t->font = TTF_OpenFont("market_deco.ttf", 25);
	t->color.r = 255;
	t->color.g = 255;
	t->color.b = 255;
	t->surface = TTF_RenderText_Solid(t->font, "Hello World!", t->color);
	t->texture = SDL_CreateTextureFromSurface(t->renderer, t->surface);
	SDL_QueryTexture(t->texture, NULL, NULL, &t->texw, &t->texh);
	t->dstrect.x = 0;
	t->dstrect.y = 0;
	t->dstrect.w = t->texw;
	t->dstrect.h = t->texh;
}

static void		ttf_destroy(t_ttf *t)
{
	SDL_DestroyTexture(t->texture);
	SDL_FreeSurface(t->surface);
	TTF_CloseFont(t->font);
	SDL_DestroyRenderer(t->renderer);
	SDL_DestroyWindow(t->window);
	TTF_Quit();
	SDL_Quit();
}

int				main(int argc, char **argv)
{
	t_ttf t;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	ttf_init(&t);
	while (!t.quit)
	{
		SDL_WaitEvent(&t.event);
		if (t.event.type == SDL_QUIT)
			t.quit = 1;
		SDL_RenderCopy(t.renderer, t.texture, NULL, &t.dstrect);
		SDL_RenderPresent(t.renderer);
	}
	ttf_destroy(&t);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 16:21:56 by acourtin          #+#    #+#             */
/*   Updated: 2018/03/28 18:15:40 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_mouse.h"

int				init(SDL_Window *window, SDL_Renderer **renderer)
{
	int img_flags;

	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		window = SDL_CreateWindow("SDL Mouse", SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, S_WTH, S_HGT, SDL_WINDOW_SHOWN);
		if (window)
		{
		  *renderer = SDL_CreateRenderer(window, -1,		\
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (*renderer)
			{
				SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				img_flags = IMG_INIT_PNG;
				if (IMG_Init(img_flags) & img_flags)
					return (1);
			}
		}
	}
	return (0);
}

int				load_media(t_button **buttons, SDL_Rect sprite_clip[4], \
					   t_texture *texture_button, SDL_Renderer *renderer)
{
	int i;

	if (!texture_button->texture_load_from_file(texture_button,
						    "button.png", renderer))
	  return (0);
	else
	{
		i = -1;
		while (++i < 4)
		{
			sprite_clip[i].x = 0;
			sprite_clip[i].y = i * 200;
			sprite_clip[i].w = B_WTH;
			sprite_clip[i].h = B_HGT;
		}
	}
	return (1);
}

void			Pclose(t_texture *texture_button, SDL_Window *window,
			     SDL_Renderer *renderer)
{
  	texture_button->texture_free(texture_button);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}

void		        events(t_main *m, SDL_Renderer *renderer)
{
	while (SDL_PollEvent(&m->e) != 0)
	{
		if (m->e.type == SDL_QUIT)
			m->quit = 1;
		m->i = -1;
		while (++m->i < 4)
			m->buttons[m->i]->button_handle_event(m->buttons[m->i], &m->e);
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	m->i = -1;
	while (++m->i < 4)
		m->buttons[m->i]->button_render(m->buttons[m->i], \
				m->texture_button, m->sprite_clip, renderer);
	SDL_RenderPresent(renderer);
}

int				main(int argc, char **args)
{
	t_main		m;
	SDL_Renderer	*renderer;
	t_button	**buttons;

	buttons = media_loader(4,
		     0, 0, 150, 0, 0, 150, 150, 150);
	m.texture_button = texture_new();
	/* m.buttons[0] = button_new(0, 0); */
	/* m.buttons[1] = button_new(150, 0); */
	/* m.buttons[2] = button_new(0, 150); */
	/* m.buttons[3] = button_new(150, 150); */
	m.buttons = buttons;
	if (init(m.window, &renderer))
	{
	  if (load_media(m.buttons, m.sprite_clip, m.texture_button, renderer))
		{
			m.quit = 0;
			while (!m.quit)
			  events(&m, renderer);
		}
	}
	Pclose(m.texture_button, m.window, renderer);
	return (0);
}

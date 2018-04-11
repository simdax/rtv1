/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 16:21:56 by acourtin          #+#    #+#             */
/*   Updated: 2018/04/11 14:33:39 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_mouse.h"
#include "libft.h"

int				init(SDL_Window *window, SDL_Renderer **renderer)
{
	int img_flags;

	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		window = SDL_CreateWindow("SDL Mouse", SDL_WINDOWPOS_UNDEFINED, \
				SDL_WINDOWPOS_UNDEFINED, S_WTH, S_HGT, SDL_WINDOW_SHOWN);
		if (window)
		{
			*renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (*renderer)
			{
				SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				img_flags = IMG_INIT_PNG;
				if (IMG_Init(img_flags) & img_flags)
					return (1);
			}
		}
		TTF_Init();
	}
	return (0);
}

void			f_pclose(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void			f_events(t_interface *m, SDL_Renderer *renderer,
		SDL_Event *e)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (m->buttons[++i])
		j++;
	m->i = -1;
	while (++m->i < j)
		m->buttons[m->i]->button_handle_event(m->buttons[m->i], e);
	m->i = -1;
	while (++m->i < j)
		m->buttons[m->i]->button_render(m->buttons[m->i], renderer);
}

void			interface_free(t_interface *m)
{
	while (*m->buttons)
	{
		(*m->buttons)->button_free(*m->buttons);
		++m->buttons;
	}
	free(m);
}

t_interface		*interface_new(void)
{
	t_interface		*interface;

	interface = ft_memalloc(sizeof(*interface));
	interface->loop = f_events;
	interface->free = interface_free;
	return (interface);
}

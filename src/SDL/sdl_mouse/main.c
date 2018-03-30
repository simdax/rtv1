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

void			Pclose(SDL_Window *window, SDL_Renderer *renderer)
{
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
  SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
  SDL_RenderClear(renderer);
  m->i = -1;
  while (++m->i < 4)
    m->buttons[m->i]->button_render(m->buttons[m->i], renderer);
  SDL_RenderPresent(renderer);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:30:51 by acourtin          #+#    #+#             */
/*   Updated: 2018/04/13 16:35:20 by acourtin         ###   ########.fr       */
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

int				main(int argc, char **args)
{
	int				quit;
	int				j;
	SDL_Event		e;
	SDL_Renderer	*renderer;
	SDL_Window		*window;
	SDL_Rect		rectangle;
	t_texture		**textures;
	t_button		*one;
	t_button		*two;
	t_button		*three;

	if (init(window, &renderer))
	{
		rectangle.x = 0;
		rectangle.y = 0;
		rectangle.w = S_WTH;
		rectangle.h = S_HGT;
		if (!(textures = textures_loader(3, renderer, "button.png",
						"button2.png", "button3.png")))
			return (0);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		one = button_new(100, 100);
		two = button_new(200, 400);
		three = button_new(500, 300);
		one->texture = textures[0];
		two->texture = textures[1];
		three->texture = textures[2];
		j = -1;
		while (++j < 4)
		{
			one->clips[j] = (SDL_Rect){0, 200, B_WTH, B_HGT};
			one->clips[j].y = 200 * j;
			two->clips[j] = (SDL_Rect){0, 200, B_WTH, B_HGT};
			two->clips[j].y = 200 * j;
			three->clips[j] = (SDL_Rect){0, 200, B_WTH, B_HGT};
			three->clips[j].y = 200 * j;
		}
		quit = 0;
		while (quit == 0)
		{
			SDL_RenderFillRect(renderer, &rectangle);
			SDL_WaitEvent(&e);
			one->button_handle_event(one, &e);
			two->button_handle_event(two, &e);
			three->button_handle_event(three, &e);
			one->button_render(one, renderer);
			two->button_render(two, renderer);
			three->button_render(three, renderer);
			SDL_RenderPresent(renderer);
			if (e.type == SDL_QUIT)
				quit = 1;
		}
	}
	button_free(one);
	button_free(two);
	button_free(three);
	f_pclose(window, renderer);
	return (0);
}

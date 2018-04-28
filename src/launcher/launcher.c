/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:13:27 by alerandy          #+#    #+#             */
/*   Updated: 2018/04/26 18:29:27 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		usage(int err)
{
	ft_printf("Une erreure est survenue.\nERR%d\n", err);
	exit(1);
}

int			init(SDL_Window *win, SDL_Renderer **render)
{
	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		if ((win = SDL_CreateWindow("RT | Launcher", SDL_WINDOWPOS_UNDEFINED, \
				SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN)))
		{
			if ((*render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED
							| SDL_RENDERER_PRESENTVSYNC)))
			{
				SDL_SetRenderDrawColor(*render, 0xFF, 0xFF, 0xFF, 0xFF);
				if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
					return (1);
			}
		}
	}
	return (0);
}

void		launcher(char **scn, int nscn)
{
	t_launch	*launcher;
	t_texture	**textures;
	t_button	**buttons;
	int			i;
	int			j;

	launcher = NULL;
	textures = NULL;
	buttons = NULL;
	if (!(launcher = ft_memalloc(sizeof(t_launch))))
		usage(0);
	if (!init(launcher->win, &(launcher->render)))
		usage(10);
	if (!(buttons = ft_memalloc(sizeof(t_button) * nscn)))
		usage(2);
	if (!(textures = textures_loader(1, launcher->render, "../../assets/_titlebutt.png")))
		usage(3);
	if (!textures[0])
		usage(4);
	SDL_SetRenderDrawColor(launcher->render, 150, 0, 0, 255);
	i = 0;
	while (i < nscn && i < 36)
	{
		buttons[i] = button_new(25 + i * (int)(i / 4) * 200, 25 + (i - 9 * (int)(i / 9)) * 61);
		if (!buttons[i])
			usage(5);
		ft_printf("Bouton %d est positionné en x : %d & y : %d.\n", i, \
				buttons[i]->position.x, buttons[i]->position.y);
		i++;
	}
	i = -1;
	while (++i < nscn)
		buttons[i]->texture = textures[0];
	i = 0;
	while (i < nscn)
	{
		j = -1;
		while (++j < 4)
		{
			buttons[i]->clips[j] = (SDL_Rect){0, 175, 175, 36};
			buttons[i]->clips[j].y = 36 * j;
		}
		i++;
	}
	while (!launcher->quit)
	{
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		SDL_WaitEvent(&(launcher->event));
		i = -1;
		while (++i < nscn)
			buttons[i]->button_handle_event(buttons[i], &(launcher->event));
		i = -1;
		while (++i < nscn)
			buttons[i]->button_render(buttons[i], launcher->render);
		SDL_RenderPresent(launcher->render);
		launcher->event.type == SDL_QUIT ? launcher->quit = 1 : 0;
	}
	exit(1);
}

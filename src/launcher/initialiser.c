/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:14:37 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/02 15:51:51 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		*open_scn(void *param)
{
	t_thrprm	*event;

	event = param;
	through_argv(event);
	event->quited = 1;
	pthread_exit(NULL);
}

int			init(SDL_Window *win, SDL_Renderer **render)
{
	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		if ((win = SDL_CreateWindow("RT | Launcher", 0, \
				SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN)))
		{
			*render = SDL_CreateRenderer(win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (*render)
			{
				SDL_SetRenderDrawColor(*render, 0xFF, 0xFF, 0xFF, 0xFF);
				TTF_Init();
				if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
					return (1);
			}
		}
	}
	return (0);
}

void		set_buttons(t_launch *launcher, t_button **buttons, \
		t_texture **textures)
{
	int		i;
	int		j;

	i = -1;
	while (++i < launcher->nb_scn && i < 36)
	{
		buttons[i] = button_new(12 + ((i * 200) % (4 * 200)), \
				12 + (i / 4) * 50, 175, 36);
		buttons[i]->func = &open_scn;
		buttons[i]->param = (void*)(launcher->scn[i]);
		!buttons[i] ? usage(5) : 0;
		buttons[i]->texture = textures[0];
		buttons[i]->t = ttf_newb(launcher->render, launcher->scn[i], \
				buttons[i], "assets/28 Days Later.ttf");
		j = -1;
		while (++j < 4)
		{
			buttons[i]->clips[j] = (SDL_Rect){0, 36, 175, 36};
			buttons[i]->clips[j].y = 36 * j;
		}
	}
}

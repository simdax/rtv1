/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:13:27 by alerandy          #+#    #+#             */
/*   Updated: 2018/04/30 16:19:57 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		open_scn(void *param)
{
	through_argv((char *)param);
}

int			init(SDL_Window *win, SDL_Renderer **render)
{
	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		if ((win = SDL_CreateWindow("RT | Launcher", SDL_WINDOWPOS_UNDEFINED, \
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
		buttons[i] = button_new(25, 25 + i * 40, 175, 36);
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

void		runner(t_launch *launcher, t_button **buttons, int nscn)
{
	int		i;

	while (!launcher->quit)
	{
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		SDL_WaitEvent(&(launcher->event));
		i = -1;
		while (++i < nscn)
			buttons[i]->button_handle_event(buttons[i], &(launcher->event));
		i = -1;
		while (++i < nscn)
		{
			buttons[i]->button_render(buttons[i], launcher->render);
			SDL_RenderCopy(launcher->render, buttons[i]->t->texture, NULL, \
					&(buttons[i]->t->dstrect));
		}
		SDL_RenderPresent(launcher->render);
		launcher->event.type == SDL_QUIT ? launcher->quit = 1 : 0;
	}
	TTF_Quit();
}

void		launcher(char **scn, int nscn)
{
	t_launch	*launcher;
	t_texture	**textures;
	t_button	**buttons;

	launcher = NULL;
	textures = NULL;
	buttons = NULL;
	!(launcher = ft_memalloc(sizeof(t_launch))) ? usage(0) : 0;
	!init(launcher->win, &(launcher->render)) ? usage(10) : 0;
	!(buttons = ft_memalloc(sizeof(t_button) * nscn)) ? usage(2) : 0;
	if (!(textures = textures_loader(1, launcher->render,\
					"assets/_titlebutt.png")))
		usage(3);
	!textures[0] ? usage(4) : 0;
	launcher->img.x = 0;
	launcher->img.y = 0;
	launcher->img.w = 800;
	launcher->img.h = 600;
	launcher->nb_scn = nscn;
	launcher->scn = scn;
	SDL_SetRenderDrawColor(launcher->render, 0, 0, 0, 255);
	set_buttons(launcher, buttons, textures);
	runner(launcher, buttons, nscn);
	exit(1);
}

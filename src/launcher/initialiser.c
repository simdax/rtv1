/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:14:37 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/10 19:17:55 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

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

void		set_msbtns(t_launch *launcher, t_button **buttons, \
		t_texture **textures)
{
	int			i;

	buttons[0] = button_new(35, 500, 175, 36);
	buttons[0]->func = &to_newscreen;
	buttons[0]->param = (void*)launcher;
	buttons[0]->texture = textures[0];
	buttons[0]->t = ttf_newb(launcher->render, "Open RT", buttons[0], \
			"assets/28 Days Later.ttf");
	buttons[1] = button_new(300, 500, 175, 36);
	buttons[1]->func = &to_rtscreen;
	buttons[1]->param = (void*)launcher;
	buttons[1]->texture = textures[0];
	buttons[1]->t = ttf_newb(launcher->render, "RTS", buttons[1], \
			"assets/28 Days Later.ttf");
	set_msbtns2(launcher, buttons, textures);
	i = -1;
	while (++i < 5 * 4)
	{
		buttons[i % 5]->clips[i / 5] = (SDL_Rect){0, 36, 175, 36};
		buttons[i % 5]->clips[i / 5].y = 36 * (i / 5);
	}
}

int			set_newbtns2(t_launch *launcher, t_button **btns, t_texture **txtr)
{
	int		i;
	int		j;

	i = -1;
	while (++i < launcher->nb_scn + 1 && i < 36)
	{
		!(btns[i] = button_new(12 + ((i * 200) % (4 * 200)), \
				200 + (i / 4) * 50, 175, 36)) ? usage(5) : 0;
		btns[i]->func = &open_scn;
		btns[i]->param = i == 0 ? "New" : (void *)(launcher->scn[i - 1]);
		btns[i]->texture = txtr[0];
		btns[i]->t = ttf_newb(launcher->render, i == 0 ? "New" : \
				launcher->scn[i - 1], btns[i], "assets/28 Days Later.ttf");
		j = -1;
		while (++j < 4)
		{
			btns[i]->clips[j] = (SDL_Rect){0, 36, 175, 36};
			btns[i]->clips[j].y = 36 * j;
		}
	}
	return (i);
}

void		set_newbtns(t_launch *launcher, t_button **buttons, \
		t_texture **textures)
{
	int		i;
	int		j;

	launcher->img.w = 800;
	launcher->img.h = 600;
	i = set_newbtns2(launcher, buttons, textures);
	!(buttons[i] = button_new(12, 150, 175, 36)) ? usage(5) : 0;
	buttons[i]->func = &to_mainscreen;
	buttons[i]->id = 1;
	buttons[i]->param = (void*)launcher;
	buttons[i]->texture = textures[0];
	buttons[i]->t = ttf_newb(launcher->render, "Home", buttons[i], \
			"assets/28 Days Later.ttf");
	j = -1;
	while (++j < 4)
	{
		buttons[i]->clips[j] = (SDL_Rect){0, 36, 175, 36};
		buttons[i]->clips[j].y = 36 * j;
	}
}

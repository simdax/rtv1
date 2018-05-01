/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:13:27 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/01 21:02:55 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		*open_scn(void *param)
{
	t_thrprm	*event;

	event = param;
	through_argv(event);
	pthread_exit(NULL);
}

void		watch_btn(t_launch *launcher, t_button **buttons, int nscn, int i)
{
	if (1 == SDL_GetWindowID(SDL_GetMouseFocus()))
		buttons[i]->button_handle_event(buttons[i], &(launcher->event));
	buttons[i]->button_render(buttons[i], launcher->render);
	SDL_RenderCopy(launcher->render, buttons[i]->t->texture, NULL, \
			&(buttons[i]->t->dstrect));
}

int			get_thr(t_launch *launcher, t_button **buttons, int i)
{
	int		j;

	if (buttons[i]->trigger)
	{
		j = 0;
		while (j < MAXTHREAD && buttons[i]->trigger)
		{
			if (!launcher->thr[j])
			{
				buttons[i]->trigger = 0;
				return (j);
			}
			else
				j++;
		}
		ft_putendl("No thread left...");
		buttons[i]->trigger = 0;
	}
	return (-1);
}

void		runner(t_launch *launcher, t_button **buttons, int nscn)
{
	int		i;
	int		j;

	while (!launcher->quit)
	{
		launcher->event.type == SDL_QUIT ? launcher->quit = 1 : 0;
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		SDL_WaitEvent(&(launcher->event));
		i = -1;
		while (++i < nscn)
		{
			watch_btn(launcher, buttons, nscn, i);
			if ((j = get_thr(launcher, buttons, i)) != -1)
				pthread_create(&(launcher->thr[j]), NULL, buttons[i]->func, \
					&((t_thrprm){buttons[i]->param, &(launcher->event)}));
		}
		SDL_RenderPresent(launcher->render);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:13:27 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/02 19:33:21 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		watch_btn(t_launch *launcher, t_button *buttons)
{
	if (1 == SDL_GetWindowID(SDL_GetMouseFocus()))
		buttons->button_handle_event(buttons, &(launcher->event));
	buttons->button_render(buttons, launcher->render);
	SDL_RenderCopy(launcher->render, buttons->t->texture, NULL, \
			&(buttons->t->dstrect));
}

void		runner(t_launch *launcher, t_button **buttons, int nscn)
{
	launcher->state = MSCREEN;
	while (!launcher->quit)
	{
		launcher->state == NEW ? new_rt(launcher, buttons, nscn) : 0;
		launcher->state == MSCREEN ? mainscreen(launcher, NULL) : 0;
		launcher->state == QUIT ? launcher->quit = 1 : 0;
	}
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
	!(buttons = ft_memalloc(sizeof(t_button) * (nscn + 1))) ? usage(2) : 0;
	if (!(textures = textures_loader(1, launcher->render,\
					"assets/_titlebutt.png")))
		usage(3);
	!textures[0] ? usage(4) : 0;
	launcher->nb_scn = nscn;
	launcher->scn = scn;
	SDL_SetRenderDrawColor(launcher->render, 0, 0, 0, 255);
	set_buttons(launcher, buttons, textures);
	runner(launcher, buttons, nscn);
	exit(1);
}

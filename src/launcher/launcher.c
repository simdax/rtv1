/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:13:27 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/04 00:30:31 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		watch_btn(t_launch *launcher, t_button *buttons)
{
	if (buttons)
	{
		if (1 == SDL_GetWindowID(SDL_GetMouseFocus()))
			buttons->button_handle_event(buttons, &(launcher->event));
		buttons->button_render(buttons, launcher->render);
		SDL_RenderCopy(launcher->render, buttons->t->texture, NULL, \
				&(buttons->t->dstrect));
	}
}

void		runner(t_launch *launcher, t_button **new_btns, \
		t_button **ms_btns, int nscn)
{
	launcher->state = MSCREEN;
	while (!launcher->quit)
	{
		launcher->state == NEW ? new_rt(launcher, new_btns, nscn) : 0;
		launcher->state == MSCREEN ? mainscreen(launcher, ms_btns) : 0;
		launcher->state == QUIT ? launcher->quit = 1 : 0;
	}
}

void		launcher(char **scn, int nscn)
{
	t_launch	*launcher;
	t_texture	**textures;
	t_button	**new_btns;
	t_button	**ms_btns;

	launcher = NULL;
	textures = NULL;
	new_btns = NULL;
	ms_btns = NULL;
	!(launcher = ft_memalloc(sizeof(t_launch))) ? usage(0) : 0;
	!init(launcher->win, &(launcher->render)) ? usage(10) : 0;
	!(new_btns = ft_memalloc(sizeof(t_button) * (nscn + 1))) ? usage(2) : 0;
	!(ms_btns = ft_memalloc(sizeof(t_button) * (7 + 1))) ? usage(2) : 0;
	if (!(textures = textures_loader(1, launcher->render,\
					"assets/_titlebutt.png")))
		usage(3);
	launcher->prm = ft_memalloc(sizeof(t_thrprm) * MAXTHREAD);
	launcher->nb_scn = nscn;
	launcher->scn = scn;
	SDL_SetRenderDrawColor(launcher->render, 0, 0, 0, 255);
	set_msbtns(launcher, ms_btns, textures);
	set_newbtns(launcher, new_btns, textures);
	runner(launcher, new_btns, ms_btns, nscn);
	free(launcher->prm);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:51:59 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/04 06:25:34 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		destroy_thrprm(t_thrprm *prm)
{
	prm->event = NULL;
	prm->scn = NULL;
	prm->quited = 0;
	prm->sdl = NULL;
	prm->opts = NULL;
}

int			get_thr(t_launch *launcher, t_button **buttons, int i, \
		t_thrprm *prm)
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
			else if (prm[j].quited)
			{
				destroy_thrprm(&prm[j]);
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

void		fill_thrprm(t_thrprm *prm, t_launch *launcher, t_button *btn)
{
	prm->event = &(launcher->event);
	prm->scn = btn->param;
	prm->quited = 0;
	prm->sdl = NULL;
	prm->opts = NULL;
}

void		new_rt(t_launch *launcher, t_button **buttons, int nscn)
{
	int			i;
	int			j;
	t_thrprm	*prm;
	t_ttf		*open;

	open = ttf_new(launcher->render, "Open scene", \
			"assets/docteur_atomic.ttf", (t_pos){35, -20, 150});
	while (launcher->state == NEW)
	{
		launcher->event.type == SDL_QUIT ? launcher->state = QUIT : 0;
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		SDL_RenderCopy(launcher->render, open->texture, NULL, &(open->dstrect));
		SDL_WaitEvent(&(launcher->event));
		i = -1;
		while (buttons[++i])
		{
			watch_btn(launcher, buttons[i]);
			if (buttons[i]->trigger && buttons[i]->id == 1)
			{
				buttons[i]->trigger = 0;
				buttons[i]->func(buttons[i]->param);
			}
			else if ((j = get_thr(launcher, buttons, i, launcher->prm)) != -1)
			{
				fill_thrprm(&(launcher->prm[j]), launcher, buttons[i]);
				pthread_create(&(launcher->thr[j]), NULL, buttons[i]->func, \
					&(launcher->prm[j]));
			}
		}
		SDL_RenderPresent(launcher->render);
	}
	ttf_destroy(open);
}

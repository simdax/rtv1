/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_rt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:51:59 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/10 19:15:36 by alerandy         ###   ########.fr       */
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
		t_thrprm **prm)
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
			else if (prm[j]->quited)
			{
				destroy_thrprm(prm[j]);
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
	prm->width = launcher->width;
	prm->height = launcher->height;
}

void		get_rt(t_launch *launcher, t_button **btns)
{
	int		i;
	int		j;

	i = -1;
	while (btns[++i])
	{
		watch_btn(launcher, btns[i]);
		if (btns[i]->id == 1 && is_triggered(btns[i]))
			btns[i]->func(btns[i]->param);
		else if ((j = get_thr(launcher, btns, i, launcher->prm)) != -1)
		{
			fill_thrprm(launcher->prm[j], launcher, btns[i]);
			pthread_create(&(launcher->thr[j]), NULL, btns[i]->func, \
				launcher->prm[j]);
		}
	}
}

void		new_rt(t_launch *launcher, t_button **buttons)
{
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
		get_rt(launcher, buttons);
		SDL_RenderPresent(launcher->render);
	}
	ttf_destroy(open);
}

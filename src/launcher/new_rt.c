/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:51:59 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/02 18:53:53 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

int			get_thr(t_launch *launcher, t_button **buttons, int i, \
		t_thrprm *prm)
{
	int		j;

	if (buttons[i]->trigger)
	{
		j = 0;
		while (j < MAXTHREAD && buttons[i]->trigger)
		{
			if (!launcher->thr[j] || prm[j].quited)
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

void		fill_thrprm(t_thrprm *prm, t_launch *launcher, t_button *btn)
{
	prm->event = &(launcher->event);
	prm->scn = btn->param;
	prm->quited = 0;
}

void		new_rt(t_launch *launcher, t_button **buttons, int nscn)
{
	int			i;
	int			j;
	t_thrprm	*prm;

	prm = ft_memalloc(sizeof(t_thrprm) * MAXTHREAD);
	while (launcher->state == NEW)
	{
		launcher->event.type == SDL_QUIT ? launcher->state = QUIT : 0;
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		SDL_WaitEvent(&(launcher->event));
		i = -1;
		while (++i < nscn + 1)
		{
			watch_btn(launcher, buttons[i]);
			if ((j = get_thr(launcher, buttons, i, prm)) != -1)
			{
				fill_thrprm(&prm[j], launcher, buttons[i]);
				pthread_create(&(launcher->thr[j]), NULL, buttons[i]->func, \
					&(prm[j]));
			}
		}
		SDL_RenderPresent(launcher->render);
	}
	free(prm);
}

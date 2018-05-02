/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:13:22 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/02 19:34:50 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

int			is_triggered(t_button *btn)
{
	if (btn)
	{
		if (btn->trigger)
		{
			btn->trigger = 0;
			return (1);
		}
	}
	btn->trigger = 0;
	return (0);
}

void		mainscreen(t_launch *launcher, t_button **buttons)
{
	int			i;
	t_ttf		*title;
	t_pos		pos;

	pos.x = 35;
	pos.y = 35;
	pos.z = 75;
	title = ttf_new(launcher->render, "RT", "assets/docteur_atomic.ttf", pos);
	while (launcher->state == MSCREEN)
	{
		launcher->event.type == SDL_QUIT ? launcher->state = QUIT : 0;
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		SDL_RenderCopy(launcher->render, title->texture, NULL, \
				&(title->dstrect));
		SDL_WaitEvent(&(launcher->event));
		i = -1;
		while (++i < 0)
		{
			watch_btn(launcher, buttons[i]);
			if ((is_triggered(buttons[i])) != -1)
				ft_putendl("Trigerred");
		}
		SDL_RenderPresent(launcher->render);
	}
	ttf_destroy(title);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:13:22 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/04 05:40:35 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

int			is_triggered(t_button *btn)
{
	if (btn != NULL)
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

t_ttf		**ttf_newscreen(t_launch *launcher)
{
	t_ttf	**titleby;
	t_pos	pos;

	titleby = NULL;
	pos.x = 500;
	pos.z = 40;
	pos.y = 0;
	titleby = multi_ttf(6, launcher->render, "assets/28 Days Later.ttf", pos,
			"RT", "by", "scornaz", "cbesse", "acourtin", "alerandy");
	pos.x = 50;
	pos.y = -70;
	pos.z = 300;
	ttf_destroy(titleby[0]);
	titleby[0] = ttf_new(launcher->render, "RT", "assets/docteur_atomic.ttf", \
			pos);
	titleby[1]->dstrect.y = titleby[2]->dstrect.y;
	titleby[1]->dstrect.x = titleby[2]->dstrect.x - titleby[1]->texw - 10;
	return (titleby);
}

void		tab_render(t_launch *launcher, t_ttf **texts)
{
	int		i;

	i = -1;
	while (texts[++i])
		SDL_RenderCopy(launcher->render, texts[i]->texture, NULL, \
				&(texts[i]->dstrect));
}

void		mainscreen(t_launch *launcher, t_button **buttons)
{
	int			i;
	t_ttf		**titleby;

	titleby = ttf_newscreen(launcher);
	while (launcher->state == MSCREEN)
	{
		launcher->event.type == SDL_QUIT ? launcher->state = QUIT : 0;
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		tab_render(launcher, titleby);
		SDL_WaitEvent(&(launcher->event));
		i = -1;
		while (++i < 1)
		{
			watch_btn(launcher, buttons[i]);
			if ((is_triggered(buttons[i])))
				buttons[i]->func(buttons[i]->param);
		}
		SDL_RenderPresent(launcher->render);
	}
	m_ttf_destroy(titleby);
}

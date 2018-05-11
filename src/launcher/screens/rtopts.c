/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtopts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:05:11 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/10 19:11:00 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		setbtn(t_launch *launcher, t_button **btns)
{
	btns[0] = button_new(15, 125, 175, 36);
	btns[0]->func = &to_rtscreen;
	btns[0]->param = (void*)launcher;
	btns[0]->texture = NULL;
	btns[0]->t = ttf_newb(launcher->render, "RETURN", btns[0], \
			"assets/28 Days Later.ttf");
}

void		filter_chng(t_thrprm *param, t_button *btn)
{
	param->sdl->filter = btn->id - 1;
	param->sdl->is_rendering = 0;
	btn->trigger = 0;
}

void		setoptsbtn(t_launch *launcher, t_button **btns, t_thrprm *param)
{
	int		i;
	char	*filter[4];

	filter[0] = "aucun";
	filter[1] = "sepia";
	filter[2] = "grayscale";
	filter[3] = "negatif";
	i = 0;
	while (++i < 5)
	{
		btns[i] = button_new(20, 125 + (50 * i), 175, 36);
		btns[i]->func = (void *)&i;
		btns[i]->param = (void *)param;
		btns[i]->id = i;
		btns[i]->t = ttf_newb(launcher->render, filter[i - 1], btns[i], \
				"assets/28 Days Later.ttf");
	}
}

void		rt_opts(t_rt *opts)
{
	t_ttf		**title;
	t_launch	*launcher;
	t_button	**btns;
	int			i;

	btns = ft_memalloc(sizeof(t_button *) * (5 + 1));
	launcher = opts->launcher;
	title = multi_ttf(2, launcher->render, "assets/bebas.ttf", \
			(t_pos){15, 80, 20}, opts->thr->scn, \
			"here you change the setting(s) of the selected RT");
	ttf_destroy(title[0]);
	title[0] = ttf_new(launcher->render, opts->thr->scn, \
			"assets/bebas.ttf", (t_pos){15, 15, 70});
	setbtn(launcher, btns);
	setoptsbtn(launcher, btns, opts->thr);
	while (opts->launcher->state == OPTS)
	{
		launcher->event.type == SDL_QUIT ? launcher->state = QUIT : 0;
		!opts->thr->sdl ? launcher->state = RTS : 0;
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		tab_render(launcher, title);
		i = 0;
		while (btns[i])
		{
			watch_btn(launcher, btns[i]);
			i == 0 && btns[i]->trigger ? btns[i]->func(btns[i]->param) : 0;
			if (btns[++i] && btns[i]->trigger)
				filter_chng(btns[i]->param, btns[i]);
		}
		SDL_WaitEvent(&(launcher->event));
		SDL_RenderPresent(launcher->render);
	}
	free(btns);
}
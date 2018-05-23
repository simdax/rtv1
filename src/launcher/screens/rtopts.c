/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtopts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:05:11 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/22 14:39:16 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rtv1.h"

static void		filter_chng(t_thrprm *param, t_button *btn)
{
	param->sdl->filter = btn->id - 1;
	param->sdl->is_rendering = 0;
	btn->trigger = 0;
}

static void		setoptsbtn(t_launch *launcher, t_button **btns, t_thrprm *param)
{
	int		i;
	char	*filter[5];

	filter[0] = "aucun";
	filter[1] = "sepia";
	filter[2] = "grayscale";
	filter[3] = "negatif";
	filter[4] = "FXAA";
	i = 0;
	btns[0] = button_new(15, 125, 175, 36);
	btns[0]->func = &to_rtscreen;
	btns[0]->param = (void*)launcher;
	btns[0]->texture = NULL;
	btns[0]->t = ttf_newb(launcher->render, "RETURN", btns[0], \
			"assets/28 Days Later.ttf");
	while (++i < 6)
	{
		btns[i] = button_new(20, 175 + (50 * i), 175, 36);
		btns[i]->func = (void *)&i;
		btns[i]->param = (void *)param;
		btns[i]->id = i;
		btns[i]->t = ttf_newb(launcher->render, filter[i - 1], btns[i], \
				"assets/28 Days Later.ttf");
	}
}

static void		slctd(t_launch *launcher, t_rt *opts)
{
	t_ttf		**info;
	t_ttf		**value;
	char		*tmp;

	if (opts->launcher->state != OPTS || !opts->thr->sdl || !opts->selected)
		return ;
	info = multi_ttf(2, launcher->render, "assets/bebas.ttf",
		(t_pos){500, 240, 30}, opts->selected->tag, "Position :");
	value = ft_memalloc(sizeof(t_ttf *) * (6 + 1));
	tmp = ft_itoa(opts->selected->position.x);
	tmp ? value[0] = ttf_new(launcher->render, tmp, "assets/bebas.ttf", \
		(t_pos){600, 289, 20}) : 0;
	tmp ? ft_strdel(&tmp) : 0;
	tmp = ft_itoa(opts->selected->position.y);
	tmp ? value[1] = ttf_new(launcher->render, tmp, "assets/bebas.ttf", \
		(t_pos){value[0]->texw + value[0]->dstrect.x + 10, 289, 20}) : 0;
	tmp ? ft_strdel(&tmp) : 0;
	tmp = ft_itoa(opts->selected->position.z);
	tmp ? value[2] = ttf_new(launcher->render, tmp, "assets/bebas.ttf", \
		(t_pos){value[1]->texw + value[1]->dstrect.x + 10, 289, 20}) : 0;
	tmp ? ft_strdel(&tmp) : 0;
	tab_render(launcher, value);
	tab_render(launcher, info);
	m_ttf_destroy(value);
	m_ttf_destroy(info);
}

static void		run(t_launch *launcher, t_rt *opts, t_ttf **title, \
		t_button **btns)
{
	int			i;

	while (opts->launcher->state == OPTS)
	{
		SDL_WaitEvent(&(launcher->event));
		launcher->event.type == SDL_QUIT ? launcher->state = QUIT : 0;
		!opts->thr->sdl ? launcher->state = RTS : 0;
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		tab_render(launcher, title);
		slctd(launcher, opts);
		opts->thr->sdl ? getobj(opts) : 0;
		i = 0;
		while (btns[i])
		{
			watch_btn(launcher, btns[i]);
			i == 0 && btns[i]->trigger ? btns[i]->func(btns[i]->param) : 0;
			if (btns[++i] && btns[i]->trigger)
				filter_chng(btns[i]->param, btns[i]);
		}
		SDL_RenderPresent(launcher->render);
	}
	opts->selected ? opts->selected->surface_color.x -= 255 : 0;
	opts->thr->sdl ? opts->thr->opts->it = ITRES : 0;
	opts->thr->sdl ? opts->selected = 0 : 0;
	opts->thr->sdl ? opts->thr->sobj = 0 : 0;
}

void			rt_opts(t_rt *opts)
{
	t_ttf		**title;
	t_launch	*launcher;
	t_button	**btns;

	btns = ft_memalloc(sizeof(t_button *) * (6 + 1));
	title = ft_memalloc(sizeof(t_ttf *) * (4 + 1));
	launcher = opts->launcher;
	title[0] = ttf_new(launcher->render, opts->thr->scn, \
			"assets/bebas.ttf", (t_pos){15, 10, 70});
	title[1] = ttf_new(launcher->render, \
			"here you change the setting(s) of the selected RT", \
			"assets/bebas.ttf", (t_pos){15, 80, 20});
	title[2] = ttf_new(launcher->render, "Filtres :", \
			"assets/bebas.ttf", (t_pos){15, 180, 35});
	title[3] = ttf_new(launcher->render, "Objet selectionne :", \
			"assets/bebas.ttf", (t_pos){490, 195, 35});
	setoptsbtn(launcher, btns, opts->thr);
	run(launcher, opts, title, btns);
	btn_clean(btns);
	m_ttf_destroy(title);
}

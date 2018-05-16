/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtopts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:05:11 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/16 18:31:24 by alerandy         ###   ########.fr       */
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
	char	*filter[4];

	filter[0] = "aucun";
	filter[1] = "sepia";
	filter[2] = "grayscale";
	filter[3] = "negatif";
	i = 0;
	btns[0] = button_new(15, 125, 175, 36);
	btns[0]->func = &to_rtscreen;
	btns[0]->param = (void*)launcher;
	btns[0]->texture = NULL;
	btns[0]->t = ttf_newb(launcher->render, "RETURN", btns[0], \
			"assets/28 Days Later.ttf");
	while (++i < 5)
	{
		btns[i] = button_new(20, 175 + (50 * i), 175, 36);
		btns[i]->func = (void *)&i;
		btns[i]->param = (void *)param;
		btns[i]->id = i;
		btns[i]->t = ttf_newb(launcher->render, filter[i - 1], btns[i], \
				"assets/28 Days Later.ttf");
	}
}

static void		getobj(t_launch *launch, t_rt *opts)
{
	int			x;
	int			y;
	t_vec3f		ray;
	t_vec3f		color;

	if (opts->thr->sdl && opts->thr->sdl->event->type == SDL_MOUSEBUTTONDOWN &&
		opts->thr->sdl->id == (int)SDL_GetWindowID(SDL_GetMouseFocus()))
	{
		SDL_GetMouseState(&x, &y);
		ray = create_ray(x, y, opts->thr->opts);
		ray = matrix_mul(opts->thr->opts->matrix, ray);
		opts->selected ? opts->selected->surface_color.x -= 255 : 0;
		opts->selected ? render(opts->thr->opts) : 0;
		opts->selected ? opts->thr->sdl->is_rendering = 0 : 0;
		opts->thr->sobj = trace(&((t_ray){INFINITY, opts->thr->opts->camorig, \
					ray, -1}), *opts->thr->opts->spheres, 0, &color);
		opts->selected = opts->thr->sobj != opts->selected ? \
						 opts->thr->sobj : 0;
		if (opts->selected)
		{
			opts->selected->surface_color.x += 255;
			render(opts->thr->opts);
			opts->thr->sdl->is_rendering = 0;
		}
		else
			opts->thr->sobj = 0;
	}
}

static void		run(t_launch *launcher, t_rt *opts, t_ttf **title, \
		t_button **btns)
{
	int			i;

	while (opts->launcher->state == OPTS)
	{
		launcher->event.type == SDL_QUIT ? launcher->state = QUIT : 0;
		!opts->thr->sdl ? launcher->state = RTS : 0;
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		tab_render(launcher, title);
		opts->thr->sdl ? getobj(launcher, opts) : 0;
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
	opts->selected ? opts->selected->surface_color.x -= 255 : 0;
	opts->thr->sdl && opts->selected ? render(opts->thr->opts) : 0;
	opts->thr->sdl ? opts->thr->sdl->is_rendering = 0 : 0;
	opts->thr->sdl ? opts->selected = 0 : 0;
}

void			rt_opts(t_rt *opts)
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
	setoptsbtn(launcher, btns, opts->thr);
	run(launcher, opts, title, btns);
	btn_clean(btns);
	m_ttf_destroy(title);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_rt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:51:59 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/12 10:51:34 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

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

static void	loading(t_launch *launcher, int j)
{
	t_texture		**txtr;
	t_ttf			*load;
	t_txt_renderer	t;
	SDL_Rect		render_quad;

	if (!(txtr = textures_loader(1, launcher->render, "assets/loading.png")))
		usage(40);
	load = ttf_new(launcher->render, "Loading...", \
			"assets/docteur_atomic.ttf", (t_pos){150, 150, 200});
	t = (t_txt_renderer){400, 400, NULL, 0, NULL};
	render_quad = (SDL_Rect){350, 350, 51, 51};
	while (!launcher->prm[j]->sdl)
	{
		t.angle += 45;
		SDL_Delay(150);
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		SDL_RenderCopy(launcher->render, load->texture, NULL, &(load->dstrect));
		SDL_RenderCopyEx(launcher->render, txtr[0]->texture, NULL, \
				&(render_quad), t.angle, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(launcher->render);
	}
	texture_free(txtr[0]);
	free(txtr);
	ttf_destroy(load);
}

void		get_rt(t_launch *launcher, t_button **btns, int *r)
{
	int			i;
	int			j;
	t_button	**tmp;

	i = -1;
	while (btns[++i])
	{
		watch_btn(launcher, btns[i]);
		if (btns[i]->id == 1 && is_triggered(btns[i]))
			btns[i]->func(btns[i]->param);
		else if (btns[i]->id == 3 && is_triggered(btns[i]))
		{
			refresh_ls(launcher);
			*r = 1;
		}
		else if ((j = get_thr(launcher, btns, i, launcher->prm)) != -1)
		{
			fill_thrprm(launcher->prm[j], launcher, btns[i]);
			pthread_create(&(launcher->thr[j]), NULL, btns[i]->func, \
				launcher->prm[j]);
			loading(launcher, j);
		}
	}
}

void		new_rt(t_launch *launcher, t_texture **txtr)
{
	t_ttf		*open;
	t_button	**btns;
	int			refresh;

	refresh_ls(launcher);
	!(btns = ft_memalloc(sizeof(t_button *) * (launcher->nb_scn + 4))) ? \
			usage(2) : set_newbtns(launcher, btns, txtr);
	open = ttf_new(launcher->render, "Open scene", \
			"assets/docteur_atomic.ttf", (t_pos){35, -20, 150});
	while (launcher->state == NEW)
	{
		launcher->event.type == SDL_QUIT ? launcher->state = QUIT : 0;
		refresh ? btn_clean(btns) : 0;
		if (refresh)
			!(btns = ft_memalloc(sizeof(t_button *) * (launcher->nb_scn + 4))) \
					? usage(2) : set_newbtns(launcher, btns, txtr);
		refresh = 0;
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		SDL_RenderCopy(launcher->render, open->texture, NULL, &(open->dstrect));
		SDL_WaitEvent(&(launcher->event));
		get_rt(launcher, btns, &refresh);
		SDL_RenderPresent(launcher->render);
	}
	btn_clean(btns);
	ttf_destroy(open);
}

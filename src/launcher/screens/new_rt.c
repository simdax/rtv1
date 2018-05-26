/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_rt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:51:59 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/25 20:57:31 by alerandy         ###   ########.fr       */
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
	while (!launcher->prm[j]->sdl && !launcher->prm[j]->quited)
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

void		get_page(t_launch *launcher, t_button **btns, int *p)
{
	int		i;
	int		nbp;

	i = 0;
	watch_btn(launcher, btns[0]);
	watch_btn(launcher, btns[1]);
	while (btns[i + 4])
		i++;
	nbp = i / 28;
	while (*p > nbp)
		(*p)--;
	if (i > 28)
	{
		*p == 0 ? 0 : watch_btn(launcher, btns[2]);
		*p == nbp ? 0 : watch_btn(launcher, btns[3]);
	}
}

void		get_rt(t_launch *laun, t_button **btns, int *r, int *page)
{
	int			i;
	int			j;
	int			b;

	i = -1;
	b = 0;
	get_page(laun, btns, page);
	while (btns[++i] && !(*r))
	{
		b > 7 && b <= 35 ? watch_btn(laun, btns[i]) : 0;
		if (btns[i]->id == 1 && is_triggered(btns[i]))
			btns[i]->func(btns[i]->param);
		else if (btns[i]->id == 3 && is_triggered(btns[i]))
			(*r) = 1;
		else if ((btns[i]->id == 421 || btns[i]->id == 420) && \
				is_triggered(btns[i]))
			(*page) += btns[i]->id == 421 ? 1 : -1;
		else if ((j = get_thr(laun, btns, i, laun->prm)) != -1)
		{
			fill_thrprm(laun->prm[j], laun, btns[i]);
			pthread_create(&(laun->thr[j]), NULL, btns[i]->func, laun->prm[j]);
			loading(laun, j);
		}
		b++ == 4 ? i = 28 * *page : 0;
	}
}

void		new_rt(t_launch *launcher, t_texture **txtr)
{
	t_ttf		*open;
	t_button	**btns;
	int			refresh;
	int			p;

	p = 0;
	refresh = 0;
	!(btns = ft_memalloc(sizeof(t_button *) * (launcher->nb_scn + 6))) ? \
			usage(2) : set_newbtns(launcher, btns, txtr);
	open = ttf_new(launcher->render, "Open scene", \
			"assets/docteur_atomic.ttf", (t_pos){35, -20, 150});
	while (launcher->state == NEW)
	{
		launcher->event.type == SDL_QUIT ? launcher->state = QUIT : 0;
		refresh ? launcher->state = MSCREEN : 0;
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		SDL_RenderCopy(launcher->render, open->texture, NULL, &(open->dstrect));
		SDL_WaitEvent(&(launcher->event));
		get_rt(launcher, btns, &refresh, &p);
		SDL_RenderPresent(launcher->render);
	}
	btn_clean(btns);
	ttf_destroy(open);
	refresh ? launcher->state = NEW : 0;
	refresh ? refresh_ls(launcher) : 0;
}

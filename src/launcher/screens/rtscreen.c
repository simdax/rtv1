/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtscreen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 08:20:46 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/05 14:21:30 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		new_runbtn(t_thrprm *prm, t_button **btn, t_launch *launcher, int i)
{
	int		j;

	!(btn[i] = button_new(12 + (((i - 1) * 200) % (4 * 200)), \
				200 + ((i - 1) / 4) * 50, 175, 36)) ? usage(5) : 0;
	btn[i]->func = NULL;
	btn[i]->param = NULL;
	btn[i]->t = ttf_newb(launcher->render, prm->scn, btn[i], \
			"assets/28 Days Later.ttf");
}

void		getrtbtns(t_launch *launcher, t_button **btns, t_texture **txtr)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < MAXTHREAD)
	{
		if (launcher->prm[i].sdl != NULL)
		{
			if (launcher->prm[i].quited == 1)
			{
				destroy_thrprm(&(launcher->prm[i]));
				launcher->thr[i--] = NULL;
				free(btns[++j]);
				btns[j] = NULL;
				i--;
				--j;
			}
			else
			{
				new_runbtn(&(launcher->prm[i]), btns, launcher, ++j);
				btns[j]->texture = txtr[0];
			}
		}
	}
}

void		setrtbtns(t_launch *launcher, t_button **btns, t_texture **txtr)
{
	int		i;
	int		j;

	i = -1;
	!(btns[0] = button_new(12, 150, 175, 36)) ? usage(5) : 0;
	btns[0]->func = &to_mainscreen;
	btns[0]->param = (void*)launcher;
	btns[0]->texture = txtr[0];
	btns[0]->t = ttf_newb(launcher->render, "Home", btns[0], \
			"assets/28 Days Later.ttf");
	getrtbtns(launcher, btns, txtr);
	while (++i < MAXTHREAD + 1 && btns[i])
	{
		j = -1;
		while (++j < 4)
		{
			btns[i]->clips[j] = (SDL_Rect){0, 36, 175, 36};
			btns[i]->clips[j].y = 36 * j;
		}
	}
}

void		cleartbtn(t_button **btns, t_ttf *title)
{
	int		i;

	i = -1;
	while (++i < MAXTHREAD + 1 && btns[i])
	{
		ttf_destroy(btns[i]->t);
		free(btns[i]);
	}
	free(btns);
	ttf_destroy(title);
}

void		rtscreen(t_launch *launcher, t_texture **txtr)
{
	int			i;
	int			j;
	t_ttf		*open;
	t_button	**btns;

	btns = ft_memalloc(sizeof(t_button *) * (MAXTHREAD + 1));
	open = ttf_new(launcher->render, "Running RT", \
			"assets/docteur_atomic.ttf", (t_pos){35, -20, 150});
	setrtbtns(launcher, btns, txtr);
	while (launcher->state == RTS)
	{
		launcher->event.type == SDL_QUIT ? launcher->state = QUIT : 0;
		SDL_RenderFillRect(launcher->render, &(launcher->img));
		SDL_RenderCopy(launcher->render, open->texture, NULL, &(open->dstrect));
		SDL_WaitEvent(&(launcher->event));
		i = -1;
		while (++i < MAXTHREAD + 1 && btns[i])
		{
			watch_btn(launcher, btns[i]);
			if (is_triggered(btns[i]))
				btns[i]->func(btns[i]->param);
		}
		SDL_RenderPresent(launcher->render);
	}
	cleartbtn(btns, open);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 08:42:34 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/16 16:11:52 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		btn_clean(t_button **btns)
{
	int		i;

	i = -1;
	if (btns)
	{
		while (btns[++i])
		{
			ttf_destroy(btns[i]->t);
			free(btns[i]);
		}
		free(btns);
	}
}

void		destroy_thrprm(t_thrprm *prm)
{
	prm->event = NULL;
	ft_strdel(&prm->scn);
	prm->quited = 0;
	prm->sdl = NULL;
	prm->opts = NULL;
}

void		fill_thrprm(t_thrprm *prm, t_launch *launcher, t_button *btn)
{
	prm->event = &(launcher->event);
	prm->scn = ft_strdup(btn->param);
	prm->quited = 0;
	prm->sdl = NULL;
	prm->opts = NULL;
	prm->width = launcher->width;
	prm->height = launcher->height;
}

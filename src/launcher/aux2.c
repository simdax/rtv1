/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:06:23 by alerandy          #+#    #+#             */
/*   Updated: 2018/06/06 13:10:37 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		getndestroy_rt(t_launch *launcher)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	launcher->event.type == SDL_QUIT ? launcher->state = QUIT : 0;
	while (i < MAXTHREAD)
		if (!launcher->thr[i])
			i++;
		else if (launcher->prm[i] && launcher->prm[i]->sdl && \
				((launcher->prm[i]->sdl && launcher->prm[i]->sdl->quit) || \
				launcher->prm[i]->quited))
		{
			if (launcher->prm[i]->sdl)
			{
				SDL_DestroyTexture(launcher->prm[i]->sdl->texture);
				SDL_DestroyRenderer(launcher->prm[i]->sdl->renderer);
				SDL_DestroyWindow(launcher->prm[i]->sdl->window);
				launcher->prm[i]->sdl->window = NULL;
			}
			destroy_thrprm(launcher->prm[i]);
			launcher->prm[i++]->quited = 1;
		}
		else
			i++;
}

void		load_sdl(t_launch *launcher, t_ttf *load, t_texture **txtr)
{
	SDL_Rect				render_quad;
	static t_txt_renderer	t = (t_txt_renderer){400, 400, NULL, 0, NULL};

	render_quad = (SDL_Rect){350, 350, 51, 51};
	t.angle += 45;
	SDL_Delay(150);
	SDL_RenderFillRect(launcher->render, &(launcher->img));
	SDL_RenderCopy(launcher->render, load->texture, NULL, &(load->dstrect));
	SDL_RenderCopyEx(launcher->render, txtr[0]->texture, NULL, \
			&(render_quad), t.angle, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(launcher->render);
}

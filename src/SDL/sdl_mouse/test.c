/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:30:51 by acourtin          #+#    #+#             */
/*   Updated: 2018/04/11 14:37:31 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_mouse.h"

int				main(int argc, char **args)
{
	t_interface		*m;
	SDL_Renderer	*renderer;
	t_texture		*textures;

	m = interface_new();
	if (init(m->window, &renderer))
	{
		if (!(m->textures = textures_loader(1, renderer, "button.png")))
			return (0);
		if (!(m->buttons = buttons_loader(9, m->textures[0],
				4, (SDL_Rect){0, 200, B_WTH, B_HGT},
				0, 0,
				S_WTH - B_WTH, 0,
				0, S_HGT - B_HGT,
				S_WTH - B_WTH, S_HGT - B_HGT,
				(S_WTH - B_WTH) / 2, (S_HGT - B_HGT) / 2,
				(S_WTH - B_WTH) / 2 - B_WTH - 4, (S_HGT - B_HGT) / 2,
				(S_WTH - B_WTH) / 2 + B_WTH + 4, (S_HGT - B_HGT) / 2,
				(S_WTH - B_WTH) / 2, (S_HGT - B_HGT) / 2 - B_HGT - 4,
				(S_WTH - B_WTH) / 2, (S_HGT - B_HGT) / 2 + B_HGT + 4)))
			return (0);
		m->quit = 0;
		while (!m->quit)
		{
			SDL_WaitEvent(&m->e);
			m->loop(m, renderer, &m->e);
			SDL_RenderPresent(renderer);
			if (m->e.type == SDL_QUIT)
				m->quit = 1;
		}
	}
	f_pclose(m->window, renderer);
	interface_free(m);
	return (0);
}

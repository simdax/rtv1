/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 23:56:52 by alerandy          #+#    #+#             */
/*   Updated: 2018/06/01 23:57:18 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "colors.h"

void			render_wait(t_sdl *sdl, t_render_opts *opts)
{
	t_ttf			*load;

	load = ttf_new(sdl->renderer, "rendering", \
			"assets/28 Days Later.ttf", (t_pos){35, 35, 80});
	SDL_RenderCopy(sdl->renderer, load->texture, NULL, &(load->dstrect));
	SDL_RenderPresent(sdl->renderer);
	render(opts);
	ttf_destroy(load);
}

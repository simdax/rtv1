/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 23:56:52 by alerandy          #+#    #+#             */
/*   Updated: 2018/06/05 14:53:46 by alerandy         ###   ########.fr       */
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

static void		sdl_putsize(t_render_opts *opts, t_sdl *sdl)
{
	printf("Window %d size changed.\nActual size : %dx%d\nNew size : %dx%d\n", \
			sdl->event->window.windowID, (int)opts->width, (int)opts->height, \
			sdl->event->window.data1, sdl->event->window.data2);
}

void			changing_res(t_render_opts *opts, t_sdl *sdl)
{
	int					i;

	i = 0;
	if (!sdl->event->window.data1 || !sdl->event->window.data2)
		return ;
	sdl_putsize(opts, sdl);
	opts->width = sdl->event->window.data1;
	opts->height = sdl->event->window.data2;
	printf("opts = %d x %d\n\n", (int)opts->width, (int)opts->height);
	free(opts->pixels);
	free(opts->rended);
	while (!(opts->pixels = ft_memalloc(sizeof(int) * opts->width * \
				opts->height)) && i < 3)
		++i;
	while (!(opts->rended = ft_memalloc(sizeof(int) * opts->width * \
					opts->height)) && i < 3)
		++i;
	i == 3 ? sdl->quit = 1 : 0;
	if (i == 3)
		return ;
	SDL_DestroyTexture(sdl->texture);
	sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGB888,
									SDL_TEXTUREACCESS_STATIC,
									opts->width, opts->height);
	opts->it = ITRES;
}

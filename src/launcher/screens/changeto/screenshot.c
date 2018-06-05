/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:49:06 by acourtin          #+#    #+#             */
/*   Updated: 2018/06/05 14:19:11 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "interface.h"

void			snap_screen(t_render_opts *opts, t_sdl *sdl)
{
	SDL_Surface			*screenshot;

	screenshot = SDL_CreateRGBSurface(0, opts->width, opts->height, 32, \
		0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(sdl->renderer, NULL, SDL_PIXELFORMAT_ARGB8888, \
		screenshot->pixels, screenshot->pitch);
	if (screenshot)
	{
		if (SDL_SaveBMP(screenshot, "screenshot.bmp") == 0)
			ft_putendl("*snap*");
		else
			ft_printf("snap failed: save fail %s\n", SDL_GetError());
		SDL_FreeSurface(screenshot);
	}
	else
		ft_printf("snap failed: surface fail %s\n", SDL_GetError());
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:49:06 by acourtin          #+#    #+#             */
/*   Updated: 2018/06/05 14:42:53 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "interface.h"

static void		remplace_space(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == '?' || str[i] == '\n')
			str[i] = '_';
	}
}

void			snap_screen(t_render_opts *opts, t_sdl *sdl)
{
	SDL_Surface			*screenshot;
	time_t				rawtime;
	struct tm			*timeinfo;
	char				*filename;
	char				*filename2;

	screenshot = SDL_CreateRGBSurface(0, opts->width, opts->height, 32, \
		0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(sdl->renderer, NULL, SDL_PIXELFORMAT_ARGB8888, \
		screenshot->pixels, screenshot->pitch);
	if (screenshot)
	{
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		filename = ft_strjoin("screenshots/", asctime(timeinfo));
		filename2 = ft_strjoin(filename, ".bmp");
		remplace_space(filename2);
		if (SDL_SaveBMP(screenshot, filename2) == 0)
			ft_printf("*snap* %s", filename2);
		SDL_FreeSurface(screenshot);
		ft_strdel(&filename);
		ft_strdel(&filename2);
	}
}

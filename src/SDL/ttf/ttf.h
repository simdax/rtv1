/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 12:39:03 by acourtin          #+#    #+#             */
/*   Updated: 2018/04/05 12:41:07 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TTF_H
# define TTF_H

# include <SDL.h>
# include <SDL_ttf.h>

typedef struct			s_ttf
{
	int				quit;
	int				texw;
	int				texh;
	SDL_Event		event;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	SDL_Color		color;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Rect		dstrect;

}						t_ttf;

#endif

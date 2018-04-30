/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 12:39:03 by acourtin          #+#    #+#             */
/*   Updated: 2018/04/30 16:11:13 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TTF_H
# define TTF_H

# include <SDL.h>
# include <SDL_ttf.h>
# include "rtv1.h"

typedef struct		s_ttf
{
	int				quit;
	int				texw;
	int				texh;
	int				tmp;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	SDL_Color		color;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Rect		dstrect;

}					t_ttf;

typedef struct		s_pos
{
	int				x;
	int				y;
	int				z;
}					t_pos;

#endif

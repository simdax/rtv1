/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:47:35 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/01 10:52:04 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "sdl_mouse.h"
# include "ttf.h"
# include "rtv1.h"

# define MAXTHREAD 2

typedef struct		s_launcher
{
	SDL_Event		event;
	SDL_Renderer	*render;
	SDL_Window		*win;
	SDL_Rect		img;
	pthread_t		thr[MAXTHREAD];
	int				max_thr;
	int				nb_scn;
	char			**scn;
	int				quit;
}					t_launch;

void				launcher(char **scn, int nscn);
void				usage(int err);

t_ttf				*ttf_new(SDL_Renderer *renderer, char *str, int x, int y);
void				ttf_destroy(t_ttf *t);
t_ttf				*ttf_newb(SDL_Renderer *renderer, char *str, \
		t_button *button, char *font);
#endif

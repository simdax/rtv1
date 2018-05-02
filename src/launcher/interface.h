/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:47:35 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/02 15:51:58 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "rtv1.h"
# include "sdl_mouse.h"

# define MAXTHREAD 5

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

typedef struct		s_thrparam
{
	char			*scn;
	SDL_Event		*event;
	int				quited;
}					t_thrprm;

int					init(SDL_Window *win, SDL_Renderer **render);
void				set_buttons(t_launch *launcher, t_button **buttons, \
		t_texture **textures);

void				*open_scn(void *param);

void				launcher(char **scn, int nscn);
void				usage(int err);
void				through_argv(t_thrprm *param);
#endif

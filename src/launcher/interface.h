/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:47:35 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/01 13:44:23 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "sdl_mouse.h"
# include "ttf.h"
# include "rtv1.h"

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
}					t_thrprm;

void				launcher(char **scn, int nscn);
void				usage(int err);
void				through_argv(t_thrprm *param);
#endif

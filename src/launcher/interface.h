/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:47:35 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/04 02:13:40 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "rtv1.h"
# include "sdl_mouse.h"

# define MAXTHREAD 5

typedef struct		s_thrparam
{
	char			*scn;
	SDL_Event		*event;
	int				quited;
	t_render_opts	*opts;
	t_sdl			*sdl;
}					t_thrprm;

typedef struct		s_launcher
{
	SDL_Event		event;
	SDL_Renderer	*render;
	SDL_Window		*win;
	SDL_Rect		img;
	pthread_t		thr[MAXTHREAD];
	t_thrprm		*prm;
	int				nb_scn;
	char			**scn;
	int				quit;
	t_estate		state;
}					t_launch;

typedef struct		s_newscreen
{
	t_launch *launcher;
	t_estate newstate;
}					t_newscreen;

int					init(SDL_Window *win, SDL_Renderer **render);
void				set_newbtns(t_launch *launcher, t_button **buttons, \
		t_texture **textures);
void				set_msbtns(t_launch *launcher, t_button **buttons, \
		t_texture **textures);

void				*open_scn(void *param);
void				*to_newscreen(void *param);
void				watch_btn(t_launch *launcher, t_button *buttons);

void				launcher(char **scn, int nscn);
void				usage(int err);
void				through_argv(t_thrprm *param);

void				new_rt(t_launch *launcher, t_button **buttons, int nscn);
void				mainscreen(t_launch *launcher, t_button **buttons);

t_ttf				**multi_ttf(int nb, SDL_Renderer *renderer, char *font, \
		t_pos pos, ...);
void				m_ttf_destroy(t_ttf **text);

void			init_sdl(t_render_opts *opts, t_thrprm *param);
#endif

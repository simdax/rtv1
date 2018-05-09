/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:47:35 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/09 15:00:00 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "rtv1.h"
# include "sdl_mouse.h"
# include "changeto.h"

# define MAXTHREAD 5

typedef enum		e_estate
{
	MSCREEN,
	OPTS,
	NEW,
	RTS,
	QUIT
}					t_estate;

typedef struct		s_thrparam
{
	char			*scn;
	SDL_Event		*event;
	int				quited;
	t_render_opts	*opts;
	t_sdl			*sdl;
	int				width;
	int				height;
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
	int				width;
	int				height;
}					t_launch;

typedef struct		s_newscreen
{
	t_launch		*launcher;
	t_estate		newstate;
}					t_newscreen;

int					init(SDL_Window *win, SDL_Renderer **render);
void				set_newbtns(t_launch *launcher, t_button **buttons, \
		t_texture **textures);
void				set_msbtns(t_launch *launcher, t_button **buttons, \
		t_texture **textures);
void				set_msbtns2(t_launch *launcher, t_button **buttons, \
		t_texture **textures);

void				watch_btn(t_launch *launcher, t_button *buttons);
int					is_triggered(t_button *btn);

void				launcher(char **scn, int nscn);
void				usage(int err);
void				through_argv(t_thrprm *param);

void				new_rt(t_launch *launcher, t_button **buttons);
void				mainscreen(t_launch *launcher, t_button **buttons);
void				rtscreen(t_launch *launcher, t_texture **txtr);

t_ttf				**multi_ttf(int nb, SDL_Renderer *renderer, char *font, \
		t_pos pos, ...);
void				m_ttf_destroy(t_ttf **text);

void				destroy_thrprm(t_thrprm *prm);
void				init_sdl(t_render_opts *opts, t_thrprm *param);
#endif

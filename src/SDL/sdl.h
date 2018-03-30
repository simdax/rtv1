#ifndef MYSDL_H
# define MYSDL_H

# include "rtv1.h"

typedef struct	s_sdl{
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture	*texture;
  int		quit;
  SDL_Event	event;
  void		(*error)(struct s_sdl *self);
  void		(*exit)(struct s_sdl *self);
}		t_sdl;

void		quit_SDL(t_sdl *sdl);
void		hard_quit_SDL(t_sdl *sdl);
void		error_SDL(t_sdl *sdl);
void		new_SDL(t_sdl *sdl, t_render_opts *opts, const char *title);

#endif

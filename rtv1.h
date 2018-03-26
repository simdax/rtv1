#ifndef RTV1_H
# define RTV1_H

# include "vec3f.h"
# include "SDL.h"
# include <pthread.h>
# include "libft.h"
# include "parser.h"
# include "sphere.h"

# define WIDTH		640
# define HEIGHT		480
# define MAX_RAY_DEPTH	5
# define BIAS		1e-4
# define BACKGROUND     0.1, 0.21, 0.7
# define IOR		1.1 

typedef struct	s_config{
  float		invWidth;
  float		invHeight;
  float		fov;
  float		aspectratio;
  float		angle;
  t_vec3f	camorig;
  t_vec3f	camdir;
}		t_config;

typedef struct	s_sdl{
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture	*texture;
  int		quit;
  SDL_Event	event;
}		t_sdl;

typedef struct	s_render_opts{
  t_obj		**spheres;
  int		*pixels;
  t_config 	*config;
  t_vec3f	camorig;
  t_vec3f	camdir;
}		t_render_opts;

typedef struct	s_thread{
  int		from;
  int		to;
  int		i;
  t_render_opts	*opts;
}		t_thread;

void		init_sdl(int *pixels, t_obj **spheres, t_config *config);
void		trace(t_hit *hit, t_obj **spheres, int depth, t_vec3f *color);
void		diffuse(t_obj **spheres, t_obj *sphere, t_hit *hit);
void		transparency(t_obj **spheres,  t_obj *sphere, t_hit *hit, int depth);
int	        render(t_render_opts *opts);
void		draw(int *pixel, int index, t_vec3f *colors);

#endif

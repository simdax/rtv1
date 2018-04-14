#ifndef RTV1_H
# define RTV1_H

# include "vec3f.h"
# include <SDL.h>
# include <pthread.h>
# include "libft.h"
# include "object.h"
# include "parser.h"
# include "globals.h"
# include "printf.h"

# define WIDTH		640
# define HEIGHT		480
# define MAX_RAY_DEPTH	5
# define BIAS		1e-4
# define BACKGROUND     0.1, 0.21, 0.7
# define IOR		1.1
# define FX			0
# define DEBUG	0

typedef struct	s_config{
  float		invWidth;
  float		invHeight;
  float		fov;
  float		aspectratio;
  float		angle;
}				t_config;

typedef struct	s_sdl{
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture	*texture;
  int			quit;
  SDL_Event		event;
}				t_sdl;

typedef struct	s_render_opts{
  t_obj		**spheres;
  int		*pixels;
  t_config 	*config;
  t_vec3f	camorig;
  t_vec3f	camdir;
    float		width;
    float		height;
    t_33mat	matrix;
}				t_render_opts;

typedef struct	s_thread{
  int		from;
  int		to;
  int		i;
  t_render_opts	*opts;
}				t_thread;

void		trace(t_ray *hit, t_obj **spheres, int depth, t_vec3f *color);
void		diffuse(t_obj **spheres, t_obj *sphere, t_ray *hit);
void		effects(t_obj **spheres,  t_obj *sphere, t_ray *hit, int depth);
void		init_sdl(t_render_opts *opts);
int	        render(t_render_opts *opts);
void		draw(int *pixel, int index, t_vec3f *colors);

#endif

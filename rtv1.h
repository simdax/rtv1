#ifndef RTV1_H
# define RTV1_H

# include "vec3f.h"
# include "SDL.h"
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
  t_vec3f	raydir;
}		t_config;

typedef struct	s_sdl{
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture	*texture;
  int		quit;
  SDL_Event	event;
}		t_sdl;

void		init_sdl(int *pixels, t_sphere **spheres, t_config *config);
void		trace(t_vec3f *rayorig, t_vec3f *raydir, t_sphere **spheres, int depth, t_vec3f *color);
void		diffuse(t_sphere **spheres, t_vec3f *phit, t_vec3f *nhit, t_sphere *sphere, t_vec3f *surface_color);
void		transparency(t_sphere **spheres, t_vec3f *phit, t_vec3f *nhit, int depth, int inside, t_vec3f *raydir, t_sphere *sphere, t_vec3f *surface_color);
void		render(t_sphere **spheres, int *pixels, t_config *config, t_vec3f *vector);

#endif

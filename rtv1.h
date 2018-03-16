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
# define BACKGROUND	vec3f_new(0.1, 0.21, 0.7)
# define IOR		1.1 

void		init_sdl();
t_vec3f		*trace(t_vec3f *rayorig, t_vec3f *raydir,
		      t_sphere **spheres, int depth);
void		diffuse(t_sphere **spheres, t_vec3f *phit, t_vec3f *nhit, t_sphere *sphere, t_vec3f **surface_color);
void		transparency(t_sphere **spheres, t_vec3f *phit, t_vec3f *nhit, int depth, int inside,
		  t_vec3f *raydir, t_sphere *sphere, t_vec3f **surface_color);

#endif

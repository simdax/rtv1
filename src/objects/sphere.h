#ifndef SPHERE_H
# define SPHERE_H

# include "vec3f/vec3f.h"

typedef struct 	s_sphere_infos {
  float		radius;
  float		reflection;
  float		transparency;
}		t_sphere_infos;
  
typedef struct 	s_sphere {
  t_vec3f	center;
  t_vec3f       surface_color;
  t_vec3f       emission_color;
  float		radius;
  float		radius2;
  float	        transparency;
  float	        reflection;
}		t_sphere;

t_sphere	*sphere_new(t_vec3f center, t_vec3f surface_color,
			    t_vec3f emission_color, t_sphere_infos infos);
void		sphere_free(t_sphere *sphere);
int		sphere_intersect(t_sphere *sphere,
				 t_vec3f *orig, t_vec3f *dir,
				 float *t0, float *t1);
void		sphere_print(t_sphere *sphere);
void		sphere_normale(t_sphere *sphere,
			       t_vec3f *raydir, t_vec3f *rayorig, float *tnear,
			       t_vec3f *nhit, t_vec3f *phit);

#endif

#include "vec3f.h"

#define MAX_RAY_DEPTH	5
#define BIAS		1e-4
#define BACKGROUND	vec3f_new(0.1, 0.21, 0.7)
#define IOR		1.1 

typedef struct 	s_sphere_infos {
  float		radius;
  float		reflection;
  float		transparency;
}		t_sphere_infos;
  
typedef struct 	s_sphere {
  t_vec3f	*center;
  t_vec3f       *surface_color;
  t_vec3f       *emission_color;
  float		radius;
  float		radius2;
  float	        transparency;
  float	        reflection;
}		t_sphere;

t_sphere	*sphere_new(t_vec3f *center, t_vec3f *surface_color,
			    t_vec3f *emission_color, t_sphere_infos infos);
void		sphere_free(t_sphere *sphere);
int		sphere_intersect(t_sphere *sphere,
				 t_vec3f *orig, t_vec3f *dir,
				 float *t0, float *t1);
t_vec3f		*trace(t_vec3f *rayorig, t_vec3f *raydir,
		      t_sphere **spheres, int depth);
void diffuse(t_sphere **spheres, t_vec3f *phit, t_vec3f *nhit, t_sphere *sphere, t_vec3f **surface_color);

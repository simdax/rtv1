#ifndef SPHERE_H
# define SPHERE_H

# include "vec3f/vec3f.h"

typedef struct 	s_sphere {
t_vec3f		center;
float		radius;
float		radius2;
}		t_sphere;

# include "object.h"

t_sphere	*sphere_new(t_vec3f center, float radius);
int		sphere_intersect(t_sphere *sphere, t_hit *hit, float *t0, float *t1);
void		sphere_print(t_sphere *sphere);
void		sphere_normale(t_sphere *sphere, t_hit *hit);

#endif

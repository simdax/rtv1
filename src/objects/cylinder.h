#ifndef CYLINDER_H
#define CYLINDER_H

# include "vec3f/vec3f.h"

typedef struct	s_cylinder{
  t_vec3f	position;
  t_vec3f       axis;
  float		radius;
}		t_cylinder; 

# include "object.h"

t_cylinder	*cylinder_new(t_vec3f	position, t_vec3f axis,
			      float radius);
int		cylinder_intersect(t_cylinder *cylinder,
				   t_hit *hit, float *t0);
void		cylinder_print(t_cylinder *cylinder);
void    	cylinder_normale(t_cylinder *cylinder, t_hit *hit);

#endif

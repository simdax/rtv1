#ifndef PLANE_H
# define PLANE_H

# include "vec3f/vec3f.h"

typedef struct	s_plane{
  t_vec3f       position;
  t_vec3f	normale;
}		t_plane;

# include "object.h"

t_plane	*plane_new(t_vec3f position, t_vec3f normale);
int	plane_intersect(t_plane *plane, t_hit *hit, float *t0);
void	plane_print(t_plane *plane);
void    plane_normale(t_plane *plane, t_hit *hit);

#endif

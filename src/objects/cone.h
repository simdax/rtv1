#ifndef CONE_H
# define CONE_H

# include "vec3f/vec3f.h"

typedef struct	s_cone
{
  float		angle;
  float		angle2;
  float		height;
  t_vec3f	tip_position;		
  t_vec3f	axis;	        
}		t_cone;

# include "object.h"

t_cone	*cone_new(float angle, float height,
		  t_vec3f tip_position, t_vec3f	axis);
int	cone_intersect(t_cone *cone, t_vec3f *orig, t_vec3f *dir, float *t0);
void	cone_print(t_cone *cone);
void    cone_normale(t_cone *cone, t_hit *hit);

#endif

#include "rtv1.h"

static inline void	search_intersection(t_obj **objects, t_ray *hit)
{
  int	i;
  float	t0;

  i = 0;
  t0 = INFINITY;  
  while(objects[i])
    {
      if (object_intersect(objects[i], hit, &t0) &&
	  t0 < hit->tnear)
	{
	  hit->tnear = t0;
	  hit->obj_index = i;
	}
      ++i;
    }
}

static inline void	ret_surface(t_obj **objects, int depth,
				    t_ray *hit, t_vec3f *color)
{
  object_normale(objects[hit->obj_index], hit);
  #ifdef FX
  if ((objects[hit->obj_index]->transparency > 0 ||
       objects[hit->obj_index]->reflection > 0) && depth < MAX_RAY_DEPTH)
    effects(objects, objects[hit->obj_index], hit, depth);
  else
  #endif
  diffuse(objects, objects[hit->obj_index], hit);
  vec3f_add2(&hit->color, &(objects[hit->obj_index]->emission_color));
  vec3f_cpy(color, &hit->color);
}

void			trace(t_ray *hit, t_obj **objects,
			      int depth, t_vec3f *color)
{
  search_intersection(objects, hit);
  if (hit->obj_index == -1)
    *color = (t_vec3f){BACKGROUND};
  else
    ret_surface(objects, depth, hit, color);
}

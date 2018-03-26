#include "rtv1.h"

static inline t_obj	*search_intersection(t_obj **objects, t_hit *hit)
{
  int i = 0;
  float t0 = INFINITY;  
  t_obj *object = 0;

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

void			ret_surface(t_obj **objects, int depth,
				    t_hit *hit, t_vec3f *color)
{
  t_vec3f	surface_color;
  t_vec3f	phit;
  t_vec3f	nhit;

  hit->phit = &phit;
  hit->nhit = &nhit;
  hit->color = &surface_color;
  hit->inside = 0;
  surface_color = (t_vec3f){0, 0, 0};
  object_normale(objects[hit->obj_index], hit);
  /* if ((objects[hit->obj_index]->transparency > 0 || */
  /*      objects[hit->obj_index]->reflection > 0) && depth < MAX_RAY_DEPTH) */
  /*   transparency(objects, objects[hit->obj_index], hit, depth); */
  /* else */
    diffuse(objects, objects[hit->obj_index], hit);
  vec3f_cpy(color, &surface_color);
  vec3f_add2(color, &(objects[hit->obj_index]->emission_color));
}

void			trace(t_hit *hit, t_obj **objects,
			      int depth, t_vec3f *color)
{
  t_obj *object = 0;
  
  search_intersection(objects, hit);
  if (hit->obj_index == -1)
    *color = (t_vec3f){BACKGROUND};
  else
    ret_surface(objects, depth, hit, color);
}

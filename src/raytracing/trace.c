#include "rtv1.h"

t_obj	*search_intersection(t_obj **spheres, t_hit *hit)
{
  int i = 0;
  float t0 = INFINITY, t1 = INFINITY;  
  t_obj *sphere = 0;

  while(spheres[i])
    {
      if (object_intersect(spheres[i], hit, &t0, &t1))
	{
	  if (t0 < *hit->tnear) {
	    *hit->tnear = t0;
	    sphere = spheres[i];
	  }
        }
      ++i;
    }
    return (sphere);
}

void		ret_surface(t_obj **spheres, int depth, t_hit *hit, t_obj *sphere,
			     t_vec3f *color)
{
  t_vec3f	surface_color;
  t_vec3f	phit;
  t_vec3f	nhit;
  int		inside;

  inside = 0;
  hit->phit = &phit;
  hit->nhit = &nhit;
  hit->inside = inside;
  surface_color = (t_vec3f){0, 0, 0};
  hit->color = &surface_color;
  object_normale(sphere, hit);
  if (vec3f_dot(hit->raydir, hit->nhit) > 0)
    {
      vec3f_negate(hit->nhit);
      inside = 1;
    }
  if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH)
    transparency(spheres, sphere, hit, depth);
  else
    diffuse(spheres, sphere, hit);
  vec3f_cpy(color, &surface_color);
  vec3f_add2(color, &(sphere->emission_color));
}

void		trace(t_vec3f *rayorig, t_vec3f *raydir, t_obj **objects, int depth,
		       t_vec3f *color)
{
  t_obj *object = 0;
  t_hit	hit;
  float tnear = INFINITY;
  
  hit = (t_hit){&tnear, rayorig, raydir, 0, 0, 0};
  object = search_intersection(objects, &hit);
  if (!object)
    *color = (t_vec3f){BACKGROUND};
  else
    ret_surface(objects, depth, &hit, object, color);
}

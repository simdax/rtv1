#include "rtv1.h"

t_obj	*search_intersection(t_obj **spheres, t_vec3f *rayorig, t_vec3f *raydir,
				    float *tnear)
{
  int i = 0;
  float t0 = INFINITY, t1 = INFINITY;  
  t_obj *sphere = 0;
  
  while(spheres[i])
    {
      if (object_intersect(spheres[i], rayorig, raydir, &t0, &t1))
	{
	  if (t0 < *tnear) {
	    *tnear = t0;
	    sphere = spheres[i];
	  }
        }
      ++i;
    }
    return (sphere);
}

void		ret_surface(t_obj **spheres, int depth, float *tnear,
			     t_vec3f *rayorig, t_vec3f *raydir, t_obj *sphere,
			     t_vec3f *color)
{
  t_vec3f	surface_color;
  t_vec3f	phit;
  t_vec3f	nhit;
  int		inside;

  inside = 0;
  surface_color = (t_vec3f){0, 0, 0};
  object_normale(sphere, &((t_hit){
	tnear, rayorig, raydir, &nhit, &phit, &(sphere->emission_color)
	  }));
  if (vec3f_dot(raydir, &nhit) > 0)
    {
      vec3f_negate(&nhit);
      inside = 1;
    }
  if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH)
    transparency(spheres, &phit, &nhit, depth, inside, raydir, sphere, &surface_color);
  else
    diffuse(spheres, &phit, &nhit, sphere, &surface_color);
  vec3f_cpy(color, &surface_color);
  vec3f_add2(color, &(sphere->emission_color));
}

void		trace(t_vec3f *rayorig, t_vec3f *raydir, t_obj **objects, int depth,
		       t_vec3f *color)
{
  float tnear = INFINITY;
  float t0 = INFINITY, t1 = INFINITY;
  t_obj *object = 0;

  object = search_intersection(objects, rayorig, raydir, &tnear);
  if (!object)
    *color = (t_vec3f){BACKGROUND};
  else
    ret_surface(objects, depth, &tnear, rayorig, raydir, object, color);
}

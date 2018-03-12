#include "rtv1.h"

void		search_intersection(t_sphere **spheres, t_vec3f *rayorig, t_vec3f *raydir,
				    float *tnear, float *t0, float *t1, t_sphere **sphere)
{
  int i = 0;
  
  while(spheres[i])
    {
      if (sphere_intersect(spheres[i], rayorig, raydir, t0, t1))
	{
	  if (*t0 < 0)
	    *t0 = *t1;
	  if (*t0 < *tnear) {
	    *tnear = *t0;
	    *sphere = spheres[i];
	  }
        }
      ++i;
    }
}

t_vec3f		*ret_surface(t_sphere **spheres, int depth, float tnear,
			     t_vec3f *rayorig, t_vec3f *raydir, t_sphere *sphere)
{
  t_vec3f *surface_color = vec3f_new_unit(0);
  t_vec3f *phit = vec3f_add(rayorig, vec3f_mul_unit(raydir, tnear));
  t_vec3f *nhit = vec3f_sub(phit, sphere->center);
  vec3f_normalize(nhit);
  int inside = 0;
  if (vec3f_dot(raydir, nhit) > 0)
    {
      vec3f_negate(nhit);
      inside = 1;
    }
  if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH)
    transparency(spheres, phit, nhit, depth, inside, raydir, sphere, &surface_color);
  else
    diffuse(spheres, phit, nhit, sphere, &surface_color);
  return (vec3f_add(surface_color, sphere->emission_color));	  
}

t_vec3f		*trace(t_vec3f *rayorig, t_vec3f *raydir,
		       t_sphere **spheres, int depth)
{
  float tnear = INFINITY;
  t_sphere *sphere = 0;
  float t0 = INFINITY, t1 = INFINITY;
  search_intersection(spheres, rayorig, raydir, &tnear, &t0, &t1, &sphere);
  if (!sphere)
    return (BACKGROUND);
  else
    return (ret_surface(spheres, depth, tnear, rayorig, raydir, sphere));
}

#include "rtv1.h"

t_sphere	*search_intersection(t_sphere **spheres, t_vec3f *rayorig, t_vec3f *raydir,
				    float *tnear)
{
  int i = 0;
  float t0 = INFINITY, t1 = INFINITY;  
  t_sphere *sphere = 0;
  
  while(spheres[i])
    {
      if (sphere_intersect(spheres[i], rayorig, raydir, &t0, &t1))
	{
	  if (t0 < 0)
	    t0 = t1;
	  if (t0 < *tnear) {
	    *tnear = t0;
	    sphere = spheres[i];
	  }
        }
      ++i;
    }
    return (sphere);
}

void		ret_surface(t_sphere **spheres, int depth, float *tnear,
			     t_vec3f *rayorig, t_vec3f *raydir, t_sphere *sphere,
			     t_vec3f *color)
{
  t_vec3f	surface_color = (t_vec3f){0, 0, 0};
  t_vec3f	phit = (t_vec3f){0, 0, 0};
  t_vec3f	nhit = (t_vec3f){0, 0, 0};
  t_vec3f	raydir2 = (t_vec3f){0, 0, 0};
  int		inside = 0;
  
  vec3f_cpy(&raydir2, raydir);
  vec3f_cpy(&phit, rayorig);
  vec3f_mul_unit2(&raydir2, *tnear);
  vec3f_add2(&phit, &raydir2);
  vec3f_cpy(&nhit, &phit);
  vec3f_sub2(&nhit, sphere->center);
  vec3f_normalize(&nhit);
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
  vec3f_add2(color, sphere->emission_color);
}

void		trace(t_vec3f *rayorig, t_vec3f *raydir, t_sphere **spheres, int depth,
		       t_vec3f *color)
{
  float tnear = INFINITY;
  float t0 = INFINITY, t1 = INFINITY;
  t_sphere *sphere = 0;

  sphere = search_intersection(spheres, rayorig, raydir, &tnear);
  if (!sphere)
    *color = (t_vec3f){BACKGROUND};
  else
    ret_surface(spheres, depth, &tnear, rayorig, raydir, sphere, color);
}

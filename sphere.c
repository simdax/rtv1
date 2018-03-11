#include "rtv1.h"

t_sphere	*sphere_new(t_vec3f *center,
			    t_vec3f *surface_color,
			    t_vec3f *emission_color,
			    t_sphere_infos infos)
{
  t_sphere	*ret = malloc(sizeof(t_sphere));
  
  ret->center = center;
  ret->radius = infos.radius;
  ret->radius2 = infos.radius * infos.radius;
  ret->surface_color = surface_color;
  ret->emission_color = emission_color;
  ret->transparency = infos.transparency;
  ret->reflection = infos.reflection;
  return (ret);
}

int		sphere_intersect(t_sphere *sphere,
			 t_vec3f *rayorig, t_vec3f *raydir,
			 float *t0, float *t1)
{
  float thc;
  t_vec3f *l;
  float tca;
  float d2; 
  
  l = vec3f_sub(sphere->center, rayorig);
  tca = vec3f_dot(l, raydir);
  if (tca < 0)
    return (0);
  d2 = vec3f_dot(l, l) - tca * tca;
  if (d2 > sphere->radius2)
    return (0);
  thc = sqrt(sphere->radius2 - d2);
  *t0 = tca - thc;
  *t1 = tca + thc;
  return (1);
}

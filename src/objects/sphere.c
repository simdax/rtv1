#include "sphere.h"

t_sphere	*sphere_new(t_vec3f center,
			    t_vec3f surface_color,
			    t_vec3f emission_color,
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
  float		thc;
  float		tca;
  float		d2;
  t_vec3f	l;

  vec3f_cpy(&l, &sphere->center);
  vec3f_sub2(&l, rayorig);
  tca = vec3f_dot(&l, raydir);
  if (tca < 0)
    return (0);
  d2 = vec3f_dot(&l, &l) - tca * tca;
  if (d2 > sphere->radius2)
    return (0);
  thc = sqrt(sphere->radius2 - d2);
  *t0 = tca - thc;
  *t1 = tca + thc;
  if (*t0 < 0)
    *t0 = *t1;
  return (1);
}

void	sphere_normale(t_sphere *sphere, t_vec3f *raydir,
		       t_vec3f *rayorig, float *tnear,
		       t_vec3f *nhit, t_vec3f *phit)
{
  t_vec3f	tmp;

  vec3f_cpy(&tmp, raydir);
  vec3f_cpy(phit, rayorig);
  vec3f_mul_unit2(&tmp, *tnear);
  vec3f_add2(phit, &tmp);
  vec3f_cpy(nhit, phit);
  vec3f_sub2(nhit, &(sphere->center));
  vec3f_normalize(nhit);  
}

void		sphere_print(t_sphere *sphere)
{
  if (&sphere->center)
    {
      printf("centre : ");
      vec3f_print(&sphere->center);
    }
  printf("radius : %g\n ///////\n", sphere->radius);
}

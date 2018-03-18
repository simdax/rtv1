#include "rtv1.h"

float mix(const float a, const float b, const float mix)
{
  return (b * mix + a * (1 - mix));
}

static void 	set_surface(t_vec3f *phit, t_vec3f *nhit,
			    t_vec3f *surface_color, t_vec3f *refldir,
			    t_sphere **spheres, int depth, float facingratio,
			    t_sphere *sphere, t_vec3f *refraction)
{
  float		fresneleffect;
  t_vec3f	tmp;
  t_vec3f	tmp2;
  t_vec3f	tmp3;

  fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
  vec3f_cpy(&tmp, nhit);
  vec3f_mul_unit2(&tmp, BIAS);
  vec3f_cpy(&tmp2, phit);
  vec3f_add2(&tmp2, &tmp);
  trace(&tmp2, refldir, spheres, depth + 1, &tmp);
  vec3f_mul_unit2(&tmp, fresneleffect);
  vec3f_cpy(&tmp2, refraction);
  vec3f_mul_unit2(&tmp2, 1 - fresneleffect * sphere->transparency);
  vec3f_cpy(&tmp3, &tmp);
  vec3f_add2(&tmp3, &tmp2);
  vec3f_mul2(&tmp3, &sphere->surface_color);
  vec3f_cpy(surface_color, &tmp3);
}

void	transparency2(t_sphere **spheres, t_vec3f *nhit, t_vec3f *phit, t_vec3f *raydir,
		      int inside, int depth, t_vec3f *refraction)
{
  float		eta;
  float		cosi;
  float		k;
  t_vec3f	refrdir;
  t_vec3f	tmp;

  eta = (inside) ? IOR : 1 / IOR;
  cosi = vec3f_dot(nhit, raydir);
  k = 1 - eta * eta * (1 - cosi * cosi);
  vec3f_cpy(&refrdir, raydir);
  vec3f_mul_unit2(&refrdir, eta);
  vec3f_cpy(&tmp, nhit);
  vec3f_mul_unit2(&tmp, eta * cosi - sqrt(k));
  vec3f_add2(&refrdir, &tmp);
  vec3f_normalize(&refrdir);
  vec3f_cpy(&tmp, nhit);
  vec3f_mul_unit2(&tmp, BIAS);
  vec3f_negate(&tmp);
  vec3f_add2(&tmp, phit);
  trace(&tmp, &refrdir, spheres, depth + 1, refraction);
}

void transparency(t_sphere **spheres, t_vec3f *phit, t_vec3f *nhit, int depth, int inside,
		  t_vec3f *raydir, t_sphere *sphere, t_vec3f *surface_color)
{
  float		facingratio;
  t_vec3f	refldir;
  t_vec3f	refraction;
  t_vec3f	tmp;

  facingratio = -vec3f_dot(raydir, nhit);
  refraction = (t_vec3f){0, 0, 0};
  vec3f_cpy(&refldir, raydir);
  vec3f_cpy(&tmp, nhit);
  vec3f_mul_unit2(&tmp, 2 * vec3f_dot(raydir, nhit));
  vec3f_sub2(&refldir, &tmp); 
  vec3f_normalize(&refldir);
  if (sphere->transparency > 0)
    transparency2(spheres, nhit, phit, raydir, inside, depth, &refraction);
  set_surface(phit, nhit, surface_color, &refldir, spheres, depth, facingratio, sphere, &refraction);
}

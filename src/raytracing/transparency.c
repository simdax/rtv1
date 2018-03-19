#include "rtv1.h"

float mix(const float a, const float b, const float mix)
{
  return (b * mix + a * (1 - mix));
}

static void 	set_surface(t_obj **spheres, t_obj *sphere, t_hit *hit, int depth)
{
  float		fresneleffect;
  t_vec3f	tmp;
  t_vec3f	tmp2;
  t_vec3f	tmp3;

  fresneleffect = mix(pow(1 - hit->facingratio, 3), 1, 0.1);
  vec3f_cpy(&tmp, hit->nhit);
  vec3f_mul_unit2(&tmp, BIAS);
  vec3f_cpy(&tmp2, hit->phit);
  vec3f_add2(&tmp2, &tmp);
  trace(&tmp2, hit->refldir, spheres, depth + 1, &tmp);
  vec3f_mul_unit2(&tmp, fresneleffect);
  vec3f_cpy(&tmp2, hit->refraction);
  vec3f_mul_unit2(&tmp2, 1 - fresneleffect * sphere->transparency);
  vec3f_cpy(&tmp3, &tmp);
  vec3f_add2(&tmp3, &tmp2);
  vec3f_mul2(&tmp3, &sphere->surface_color);
  vec3f_cpy(hit->color, &tmp3);
}

void	transparency2(t_obj **spheres, t_hit *hit, int depth)
{
  float		eta;
  float		cosi;
  float		k;
  t_vec3f	refrdir;
  t_vec3f	tmp;

  eta = (hit->inside) ? IOR : 1 / IOR;
  cosi = vec3f_dot(hit->nhit, hit->raydir);
  k = 1 - eta * eta * (1 - cosi * cosi);
  vec3f_cpy(&refrdir, hit->raydir);
  vec3f_mul_unit2(&refrdir, eta);
  vec3f_cpy(&tmp, hit->nhit);
  vec3f_mul_unit2(&tmp, eta * cosi - sqrt(k));
  vec3f_add2(&refrdir, &tmp);
  vec3f_normalize(&refrdir);
  vec3f_cpy(&tmp, hit->nhit);
  vec3f_mul_unit2(&tmp, BIAS);
  vec3f_negate(&tmp);
  vec3f_add2(&tmp, hit->phit);
  trace(&tmp, &refrdir, spheres, depth + 1, hit->refraction);
}

void	transparency(t_obj **spheres, t_obj *sphere, t_hit *hit, int depth)
{
  float		facingratio;
  t_vec3f	refldir;
  t_vec3f	refraction;
  t_vec3f	tmp;

  facingratio = -vec3f_dot(hit->raydir, hit->nhit);
  refraction = (t_vec3f){0, 0, 0};
  vec3f_cpy(&refldir, hit->raydir);
  vec3f_cpy(&tmp, hit->nhit);
  vec3f_mul_unit2(&tmp, 2 * vec3f_dot(hit->raydir, hit->nhit));
  vec3f_sub2(&refldir, &tmp); 
  vec3f_normalize(&refldir);
  hit->facingratio = facingratio;
  hit->refldir = &refldir;
  hit->refraction = &refraction;
  if (sphere->transparency > 0)
    transparency2(spheres, hit, depth);
  set_surface(spheres, sphere, hit, depth);
}

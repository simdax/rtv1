#include "rtv1.h"

float mix(const float a, const float b, const float mix)
{
  return (b * mix + a * (1 - mix));
}

void transparency(t_sphere **spheres, t_vec3f *phit, t_vec3f *nhit, int depth, int inside,
		  t_vec3f *raydir, t_sphere *sphere, t_vec3f **surface_color)
{
  float facingratio = -vec3f_dot(raydir, nhit);
  float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
  t_vec3f *refldir = vec3f_sub(raydir, vec3f_mul_unit(nhit, 2 * vec3f_dot(raydir, nhit)));
  vec3f_normalize(refldir);
  t_vec3f *reflection = trace(vec3f_add(phit, vec3f_mul_unit(nhit, BIAS)),
			      refldir, spheres, depth + 1);
  t_vec3f *refraction = vec3f_new_unit(0);
  if (sphere->transparency > 0)
    {
      float eta = (inside) ? IOR : 1 / IOR;
      float cosi = vec3f_dot(nhit, raydir);
      float k = 1 - eta * eta * (1 - cosi * cosi);
      t_vec3f *refrdir = vec3f_add(vec3f_mul_unit(raydir, eta),
				   vec3f_mul_unit(nhit, eta * cosi - sqrt(k)));
      vec3f_normalize(refrdir);
      refraction = trace(vec3f_sub(phit, vec3f_mul_unit(nhit, BIAS)), refrdir, spheres, depth + 1);
    }
  *surface_color = vec3f_mul(vec3f_add(vec3f_mul_unit(reflection, fresneleffect),
				      vec3f_mul_unit(refraction, 1 - fresneleffect * sphere->transparency)),
			    sphere->surface_color);
}

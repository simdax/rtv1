#include "rtv1.h"

void		intersection(int i, t_sphere **spheres, t_vec3f *light_direction,
			     t_vec3f *phit, t_vec3f *nhit, t_vec3f **transmission)
{
  int j = 0;
  while (spheres[j])
    {
      if (i != j)
	{
	  float t0, t1;
	  if (sphere_intersect(spheres[j],
			       vec3f_add(phit, vec3f_mul_unit(nhit, BIAS)),
			       light_direction, &t0, &t1))
	    {
	      *transmission = vec3f_new_unit(0);
	      break;
	    }
	}
      ++j;
    }  
}

void		diffuse(t_sphere **spheres, t_vec3f *phit, t_vec3f *nhit, t_sphere *sphere,
			t_vec3f **surface_color)
{
  int i =0;
  while(spheres[i])
    {
      if (spheres[i]->emission_color->x > 0)
	{
	  t_vec3f *transmission = vec3f_new_unit(1);
	  t_vec3f *light_direction = vec3f_sub(spheres[i]->center, phit);
	  vec3f_normalize(light_direction);
	  intersection(i, spheres, light_direction, phit, nhit, &transmission);
	  *surface_color = vec3f_add(*surface_color,
				     vec3f_mul(vec3f_mul_unit(vec3f_mul(sphere->surface_color, transmission),
							      fmax(0.0, vec3f_dot(nhit, light_direction))),
					       spheres[i]->emission_color));
	}
      ++i;
    }
}

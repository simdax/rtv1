#include "rtv1.h"

void		intersection(int i, t_sphere **spheres, t_vec3f *light_direction,
			     t_vec3f *phit, t_vec3f *nhit, t_vec3f *transmission)
{
  float		t0;
  float		t1;
  t_vec3f	tmp;
  t_vec3f	tmp2;
  int		j;

  vec3f_cpy(&tmp, phit);
  vec3f_cpy(&tmp2, nhit);
  vec3f_mul_unit2(&tmp2, BIAS);
  vec3f_add2(&tmp, &tmp2);
  t0 = t1 = j = 0;
  while (spheres[j])
    {
      if (i != j)
	{
	  if (sphere_intersect(spheres[j], &tmp, light_direction, &t0, &t1))
	    {
	      vec3f_set(transmission, 0, 0, 0);
	      break;
	    }
	}
      ++j;
    }
}

void		set_surface(t_vec3f *surface_color, t_vec3f *sphere_surface_color,
			    t_vec3f *transmission, t_vec3f *nhit, t_vec3f *light_direction,
			    t_vec3f *emission_color)
{
  float max;
  t_vec3f tmp;
  t_vec3f tmp_surface_color;

  max = fmax(0.0, vec3f_dot(nhit, light_direction));
  vec3f_cpy(&tmp, sphere_surface_color);
  vec3f_mul2(&tmp, transmission);
  vec3f_mul_unit2(&tmp, max);
  vec3f_mul2(&tmp, emission_color);
  vec3f_cpy(&tmp_surface_color, surface_color);
  vec3f_add2(&tmp_surface_color, &tmp);
  vec3f_cpy(surface_color, &tmp_surface_color);
}

void		diffuse(t_sphere **spheres, t_vec3f *phit, t_vec3f *nhit, t_sphere *sphere,
			t_vec3f *surface_color)
{
  int i;
  t_vec3f transmission;
  t_vec3f tmp;
  t_vec3f light_direction;

  i = 0;
  while(spheres[i])
    {
      if (spheres[i]->emission_color.x > 0)
	{
	  vec3f_set(&transmission, 1, 1, 1);
	  vec3f_cpy(&tmp, &(spheres[i]->center));
	  vec3f_sub2(&tmp, phit);
	  vec3f_cpy(&light_direction, &tmp);
	  vec3f_normalize(&light_direction);
	  intersection(i, spheres, &light_direction, phit, nhit, &transmission);
	  set_surface(surface_color, &(sphere->surface_color), &transmission, nhit, &light_direction, &(spheres[i]->emission_color));
	}
      ++i;
    }
}

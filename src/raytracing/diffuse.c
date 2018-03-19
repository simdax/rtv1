#include "rtv1.h"

void		intersection(int i, t_obj **spheres, t_vec3f *light_direction,
			     t_hit *hit)
{
  float		t0;
  float		t1;
  t_vec3f	tmp;
  t_vec3f	tmp2;
  int		j;

  vec3f_cpy(&tmp, hit->phit);
  vec3f_cpy(&tmp2, hit->nhit);
  vec3f_mul_unit2(&tmp2, BIAS);
  vec3f_add2(&tmp, &tmp2);
  t0 = t1 = j = 0;
  while (spheres[j])
    {
      if (i != j)
	{
	  if (sphere_intersect(spheres[j]->obj.sphere, &tmp, light_direction, &t0, &t1))
	    {
	      hit->transmission = 0;
	      break;
	    }
	}
      ++j;
    }
}

void		set_surface(t_hit *hit, t_vec3f *sphere_surface_color,
			    t_vec3f *light_direction, t_vec3f *emission_color)
{
  float		max;
  t_vec3f	tmp;
  t_vec3f	tmp_surface_color;

  max = fmax(0.0, vec3f_dot(hit->nhit, light_direction));
  vec3f_cpy(&tmp, sphere_surface_color);
  vec3f_mul_unit2(&tmp, hit->transmission);
  vec3f_mul_unit2(&tmp, max);
  vec3f_mul2(&tmp, emission_color);
  vec3f_cpy(&tmp_surface_color, hit->color);
  vec3f_add2(&tmp_surface_color, &tmp);
  vec3f_cpy(hit->color, &tmp_surface_color);
}

void		diffuse(t_obj **spheres, t_obj *sphere, t_hit *hit)
{
  int		i;
  t_vec3f	tmp;
  t_vec3f	light_direction;
  t_obj		*light;
  
  i = 0;
  while(spheres[i])
    {
      if (ft_strequ(spheres[i]->tag, "light"))
	{
	  light = spheres[i];
	  hit->transmission = 1;
	  vec3f_cpy(&tmp, &(light->obj.sphere->center));
	  vec3f_sub2(&tmp, hit->phit);
	  vec3f_cpy(&light_direction, &tmp);
	  vec3f_normalize(&light_direction);
	  intersection(i, spheres, &light_direction, hit);
	  set_surface(hit, &(sphere->surface_color), &light_direction, &(light->emission_color));
	}
      ++i;
    }
}

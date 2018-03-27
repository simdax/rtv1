#include "rtv1.h"

static void	intersection(int i, t_obj **objects, t_vec3f light_direction,
			     t_ray *hit)
{
  float		t0;
  t_vec3f	tmp;
  t_vec3f	tmp2;
  int		j;

  vec3f_cpy(&tmp, &hit->phit);
  vec3f_cpy(&tmp2, &hit->nhit);
  vec3f_mul_unit2(&tmp2, BIAS);
  vec3f_add2(&tmp, &tmp2);
  t0 = INFINITY;
  j = 0;
  while (objects[j])
    {
      if (i != j)
	{
	  if (object_intersect(objects[j], &((t_ray){INFINITY, tmp, light_direction}), &t0))
	    {
	      hit->transmission = 0;
	      break;
	    }
	}
      ++j;
    }
}

static void	set_surface(t_ray *hit, t_vec3f *object_surface_color,
			    t_vec3f *light_direction, t_vec3f *emission_color)
{
  float		max;
  t_vec3f	tmp;
  t_vec3f	tmp_surface_color;

  max = fmax(0.0, vec3f_dot(&hit->nhit, light_direction));
  vec3f_cpy(&tmp, object_surface_color);
  vec3f_mul_unit2(&tmp, hit->transmission);
  vec3f_mul_unit2(&tmp, max);
  vec3f_mul2(&tmp, emission_color);
  vec3f_cpy(&tmp_surface_color, &hit->color);
  vec3f_add2(&tmp_surface_color, &tmp);
  vec3f_cpy(&hit->color, &tmp_surface_color);
}

void		diffuse(t_obj **objects, t_obj *object, t_ray *hit)
{
  int		i;
  t_vec3f	light_direction;
  float		light_distance;

  i = 0;
  while(objects[i])
    {
      if (ft_strequ(objects[i]->tag, "light"))
	{
	  hit->transmission = 1;
	  vec3f_cpy(&light_direction, &(objects[i]->obj.sphere->center));
	  vec3f_sub2(&light_direction, &hit->phit);
	  vec3f_normalize(&light_direction);
	  intersection(i, objects, light_direction, hit);
	  set_surface(hit, &(object->surface_color), &light_direction,
		   &(objects[i]->emission_color));
	}
      ++i;
    }
}

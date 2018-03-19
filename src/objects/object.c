#include "object.h"

t_obj object_new(char *type, char *parent)
{
  t_obj	new;

  new.tag = type;
  new.reflection = 0;
  new.transparency = 0;
  new.emission_color = (t_vec3f){0, 0, 0};
  new.surface_color = (t_vec3f){0, 0, 0};
  if (ft_strequ(type, "light") || ft_strequ(type, "sphere"))
    new.obj.sphere = sphere_new((t_vec3f){0, 0, 0},
				(t_vec3f){0, 0, 0},
				(t_vec3f){0, 0, 0},
				(t_sphere_infos){0, 0, 0});
  return (new);
}

void	del_object(void *c, size_t size)
{
  t_obj		*content;

  /* content = c; */
  /* if (content) */
  /*   { */
  /*     free(content->tag); */
  /*     content->tag = 0; */
  /*     //free(content->obj.sphere); */
  /*   } */
  /* free(content); */
  /* content = 0; */
}

void	object_set(t_obj *obj, char *prop, char *type, void *val)
{
  if (ft_strequ(prop, "position"))
    vec3f_set(&(obj->obj.sphere->center),
	      ((float*)val)[0],
	      ((float*)val)[1],
	      ((float*)val)[2]);
  else if (ft_strequ(prop, "radius"))
    {
      obj->obj.sphere->radius = *((float*)val);
      obj->obj.sphere->radius2 = obj->obj.sphere->radius * obj->obj.sphere->radius;
    }
  else if (ft_strequ(prop, "reflection"))
    obj->reflection = *((float*)val);
  else if (ft_strequ(prop, "transparency"))
    obj->transparency = *((float*)val);
  if (ft_strequ(prop, "color"))
    {
      if (ft_strequ(type, "light"))
	{
	  vec3f_set(&(obj->emission_color),
		    ((float*)val)[0],
		    ((float*)val)[1],
		    ((float*)val)[2]);
	  vec3f_set(&(obj->surface_color), 0, 0, 0);
	}
      else 
	{
	  vec3f_set(&(obj->surface_color),
		    ((float*)val)[0],
		    ((float*)val)[1],
		    ((float*)val)[2]);
	  vec3f_set(&(obj->emission_color), 0, 0, 0);
	}
    }
}

void	object_normale(t_obj *obj, t_hit *hit)
{
  if (ft_strequ(obj->tag, "sphere"))
    sphere_normale(obj->obj.sphere, hit);
  else if (ft_strequ(obj->tag, "light"))
    sphere_normale(obj->obj.sphere, hit);
  /* else if (ft_strequ(obj->tag, "cone")) */
  /*   cone_normale(obj->obj); */
  /* else if (ft_strequ(obj->tag, "cylinder")) */
  /*   cylinder_normale(obj->obj); */
  else
    printf("pas de normale");
}

int	object_intersect(t_obj *obj, t_hit *hit,
			 float *t0, float *t1)
{
  if (ft_strequ(obj->tag, "sphere"))
    return (sphere_intersect(obj->obj.sphere, hit, t0, t1));
  else if (ft_strequ(obj->tag, "light"))
    return (sphere_intersect(obj->obj.sphere, hit, t0, t1));
  /* else if (ft_strequ(obj->tag, "cone")) */
  /*   cone_intersect(obj->obj); */
  /* else if (ft_strequ(obj->tag, "cylinder")) */
  /*   cylinder_intersect(obj->obj); */
  else
    {
      //      printf("pas d'intersection");
      return (0);
    }
}

void	object_print(t_obj *obj)
{
  printf("type : %s @ %p\n", obj->tag, obj->obj);
  printf("emissionColor : ");
  vec3f_print(&(obj->emission_color));
  printf("surfaceColor : ");
  vec3f_print(&(obj->surface_color));
  if (ft_strequ(obj->tag, "sphere"))
    sphere_print(obj->obj.sphere);
  if (ft_strequ(obj->tag, "light"))
    sphere_print(obj->obj.sphere);
}

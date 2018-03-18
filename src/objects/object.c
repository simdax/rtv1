#include "object.h"

t_obj object_new(char *type, char *parent)
{
  t_obj	new;

  new.tag = type;
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

  content = c;
  if (content)
    {
      free(content->tag);
      content->tag = 0;
      //free(content->obj.sphere);
    }
  free(content);
  content = 0;
}

void	object_set(t_obj *obj, char *prop, char *type, void *val)
{
  t_vec3f	*v;
  
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
    obj->obj.sphere->reflection = *((float*)val);
  else if (ft_strequ(prop, "transparency"))
    obj->obj.sphere->transparency = *((float*)val);
  if (ft_strequ(prop, "color"))
    {
      if (ft_strequ(type, "sphere"))
	vec3f_set(&(obj->obj.sphere->surface_color),
		  ((float*)val)[0],
		  ((float*)val)[1],
		  ((float*)val)[2]);
      else if (ft_strequ(type, "light"))
	vec3f_set(&(obj->obj.sphere->emission_color),
		  ((float*)val)[0],
		  ((float*)val)[1],
		  ((float*)val)[2]);
    }
}

void	object_print(t_obj *obj)
{
  printf("type : %s @ %p\n", obj->tag, obj->obj.sphere);
  if (ft_strequ(obj->tag, "sphere"))
    sphere_print(obj->obj.sphere);
  if (ft_strequ(obj->tag, "light"))
    sphere_print(obj->obj.sphere);
}

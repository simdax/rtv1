#include "object.h"

void	*object_new(char *type, char *parent)
{
  t_obj	*new;

  new = malloc(sizeof(*new));
  new->tag = type;
  if (ft_strequ(type, "light") || ft_strequ(type, "sphere"))
      new->obj.sphere = sphere_new(vec3f_new_unit(0),
				   vec3f_new_unit(0),
				   vec3f_new_unit(0),
				   (t_sphere_infos){0, 0, 0});
  return (new);
}

void	object_set(t_obj *obj, char *prop, char *type, void *val)
{
  t_vec3f	*v;
  
  if (ft_strequ(prop, "position"))
    {
      obj->obj.sphere->center = vec3f_new(((float*)val)[0],
					  ((float*)val)[1],
					  ((float*)val)[2]);
    }
  if (ft_strequ(prop, "radius"))
    {
      obj->obj.sphere->radius = *((float*)val);
      obj->obj.sphere->radius2 = obj->obj.sphere->radius * obj->obj.sphere->radius;
    }
  if (ft_strequ(prop, "reflection"))
    obj->obj.sphere->reflection = *((float*)val);
  if (ft_strequ(prop, "transparency"))
    obj->obj.sphere->transparency = *((float*)val);
  if (ft_strequ(prop, "position"))
    {
      obj->obj.sphere->center = vec3f_new(((float*)val)[0],
					  ((float*)val)[1],
					  ((float*)val)[2]);
    }
  if (ft_strequ(prop, "color"))
    {
      v = vec3f_new(((float*)val)[0],
		    ((float*)val)[1],
		    ((float*)val)[2]);
      if (ft_strequ(type, "sphere"))
	obj->obj.sphere->surface_color = v; 
      else if (ft_strequ(type, "light"))
	obj->obj.sphere->emission_color = v;
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

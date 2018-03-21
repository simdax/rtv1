#include "object.h"
#include "parser.h"

void		cpy(t_list *elem, void *arg)
{
  t_obj	***spheres;

  spheres = arg;
  **spheres = ((t_obj*)elem->content);//->obj.sphere;
  (*spheres)++;
}

t_obj	**to_array(t_list *objects)
{
  t_obj	**spheres;
  t_obj	**copy;
  int		size;

  size = ft_lstsize(objects);
  spheres = malloc(sizeof(t_obj*) * (size + 1));
  copy = spheres;
  ft_lstiter2(objects, cpy, &copy);
  spheres[size] = 0;
  ft_lstdel(&objects, del_object);
  return (spheres);
}

t_obj    	**configure(char *config_file)
{
  return(to_array(read_configuration(config_file, "configs/rules")));
}

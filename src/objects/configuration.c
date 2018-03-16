#include "object.h"
#include "parser.h"

void		cpy(t_list *elem, void *arg)
{
  t_sphere	***spheres;

  spheres = arg;
  **spheres = ((t_obj*)elem->content)->obj.sphere;
  (*spheres)++;
}

t_sphere	**to_array(t_list *objects)
{
  t_sphere	**spheres;
  t_sphere	**copy;
  int		size;

  size = ft_lstsize(objects);
  spheres = malloc(sizeof(t_sphere*) * (size + 1));
  copy = spheres;
  ft_lstiter2(objects, cpy, &copy);
  copy[size] = 0;
  return (spheres);
}

t_sphere    	**configure(char *config_file)
{
  return(to_array(read_configuration(config_file, "rules")));
}

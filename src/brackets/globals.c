#include "parser.h"

void	globals_set(t_globals *globals, char *prop, char *type, void *val)
{
  if (ft_strequ(prop, "size"))
    {
      globals->width = ((int*)val)[0];
      globals->height = ((int*)val)[1];
    }
  else if (ft_strequ(prop, "from"))
    globals->from = *(t_vec3f*)val;
  else if (ft_strequ(prop, "to"))
    globals->to = *(t_vec3f*)val;
  else
    printf("no way for %s in %s!\n", prop, type);
}

void	globals_print(t_globals *globals)
{
  printf("%d et %d: \n", globals->width, globals->height);
  vec3f_print(&globals->from);
  vec3f_print(&globals->to);
}

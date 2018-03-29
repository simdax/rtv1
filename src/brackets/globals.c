#include "parser.h"

void	globals_set(t_globals *globals, char *prop, char *type, void *val)
{
  if (ft_strequ(prop, "size"))
    {
      globals->width = ((int*)val)[0];
      globals->height = ((int*)val)[1];
    }
  else if (ft_strequ(prop, ""))
    {
      globals->width = ((int*)val)[0];
      globals->height = ((int*)val)[0];
    }
}

void	globals_print(t_globals *globals)
{
  printf("%d et %d: \n", globals->width, globals->height);
  vec3f_print(&globals->from);
  vec3f_print(&globals->to);
}

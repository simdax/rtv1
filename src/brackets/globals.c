#include "parser.h"

void	globals_set(t_globals *globals, char *prop, char *type, void *val)
{
  if (ft_strequ(prop, "window"))
    {
      globals->width = ((int*)val)[0];
      globals->height = ((int*)val)[0];
    }
  else if (ft_strequ(prop, ""))
    {
      globals->width = ((int*)val)[0];
      globals->height = ((int*)val)[0];
    }
}

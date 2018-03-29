#include <stdarg.h>
#include "sdl_mouse.h"

t_button	**media_loader(int nb, ...)
{
  va_list	ap;
  t_button	**ptr;
  int		i;
  
  i = 0;
  ptr = (t_button**)malloc(sizeof(t_button*) * nb + 1);
  va_start(ap, nb);
  while (i < nb)
    {
      ptr[i] = button_new(va_arg(ap, int), va_arg(ap, int));
      ++i;
    }
  ptr[i] = 0;
  va_end(ap);
  return (ptr);
}

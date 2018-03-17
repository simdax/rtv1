#include "parser.h"

void	po(t_list *el)
{
  t_obj	*obj;

  obj = (t_obj*)el->content;
  if (obj)
    object_print(obj);
}


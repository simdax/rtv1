#include "parser.h"

t_data	*new_data(char type, void *d)
{
  t_data	*data = 0;

  data = malloc(sizeof(*data));
  data->type = type;
  if (type == 'l')
    data->data.list = d;
  else if (type == 's')
    data->data.string = d;
  return (data);
}

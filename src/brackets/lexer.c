#include "parser.h"

static void	putstr(char **buf, t_list **content)
{
  char const	*cpy;
  t_data	*data;
  
  cpy = *buf;
  while (**buf && !(**buf == ')' || **buf == '('))
      *buf += 1;
  data = malloc(sizeof(*data));
  data->type = 's';
  data->data.string = ft_strsub(cpy, 0, *buf - cpy);
  ft_lstaddlast(content, ft_lstnew(data, sizeof(*data)));
}

t_list	*lex(char **buf)
{
  t_list	*inside;
  t_list	*tmp;
  
  inside = 0;
  while (**buf)
    {
      if (**buf == '(')
	{
	  ++(*buf);
	  tmp = ft_lstnew(new_data('l', lex(buf)), sizeof(t_data));
	  ft_lstaddlast(&(inside), tmp);
	}
      else if (**buf == ')')
	{
	  ++(*buf);
	  return (inside);
	}
      else if (ft_issep(**buf))
	++(*buf);
      else
	putstr(buf, &inside);
    }
  return (inside);
}

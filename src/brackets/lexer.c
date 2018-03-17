#include "parser.h"

static void	putstr(char **buf, t_list **content)
{
  char const	*cpy;
  char 		*name;
  t_data	data;
  
  cpy = *buf;
  while (**buf && !(**buf == ')' || **buf == '('))
      *buf += 1;
  data.type = 's';
  name = ft_strsub(cpy, 0, *buf - cpy);  
  data.data.string = ft_strtrim(name);
  free(name);
  ft_lstaddlast(content, ft_lstnew(&data, sizeof(data)));
}

t_list	*lex_f(char **buf)
{
  t_list	*inside;
  t_data	data;
  
  inside = 0;
  while (**buf)
    {
      if (**buf == '(')
	{
	  ++(*buf);
	  data = (new_data2('l', lex_f(buf)));
	  ft_lstaddlast(&inside, ft_lstnew(&data, sizeof(t_data)));
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

t_list	*lex(char *buf)
{
  char	*cpy;

  cpy = buf;
  return (lex_f(&cpy));
}

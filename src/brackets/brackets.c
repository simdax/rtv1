#include "stdio.h"
#include "libft.h"

typedef struct	s_data{
  char		type;
  union 	u_data{
    char	*string;
    t_list	*list;    
  }		data;
}		t_data;

void	print(char **buf, t_list **content)
{
  char const	*cpy;
  t_data	*data;
  
  cpy = *buf;
  while (**buf && !(**buf == ')' || **buf == '('))
      *buf += 1;
  data = malloc(sizeof(*data));
  data->type = 's';
  data->data.string = ft_strsub(cpy, 0, *buf - cpy);
  ft_lstadd(content, ft_lstnew(data, sizeof(*data)));
}

t_list	*brackets(char **buf)
{
  t_list	*inside = 0;
  t_data	*data = 0;
  
  inside = ft_lstnew(0, sizeof(t_list*));
  while (**buf)
    {
      if (**buf == '(')
	{
	  ++(*buf);
	  data = malloc(sizeof(*data));
	  data->type = 'l';
	  data->data.list = brackets(buf);
	  ft_lstadd(&(inside), ft_lstnew(data, sizeof(*data)));
	}
      else if (**buf == ')')
	{
	  ++(*buf);
	  return (inside);
	}
      else if (ft_issep(**buf))
	++(*buf);
      else
	print(buf, &inside);
    }
  return (inside);
}

void	pprint(t_list *list)
{
  t_data	*content;
  
  while (list)
    {
      content = list->content;
      if (content)
	{
	  if (content->type == 's')
	    printf("%s", content->data.string);
	  if (content->type == 'l')
	    pprint(content->data.list);
	}
      list = list->next;
    }
}

int	main(int argc, char **argv)
{
  t_list	*content;

  if (argc > 1)
    while(*(++argv))
      {
  	content = brackets(&(*argv));
	pprint(content);
	printf("\n");
      }
  return (0);
}

#include "parser.h"

void	pprint(t_list *list, int level)
{
  t_data	*content;
  
  while (list)
    {
      content = list->content;
      if (content)
	{
	  if (content->type == 's')
	    printf("%d : %s\n", level, content->data.string);
	  if (content->type == 'l')
	    pprint(content->data.list, level + 1);
	}
      list = list->next;
    }
}

t_list	*go(char *buf)
{
  t_list	*content;

  content = brackets(&buf);
  pprint(content, 0);
  return (content);
}

int	main(int argc, char **argv)
{
  char		*tmp_types;
  char		*tmp_tree;
  t_list	*objects;
  t_list	*tree;

  tmp_types = get_file_content("types");
  tmp_tree = get_file_content("config");
  objects = go(tmp_types);
  tree = go(tmp_tree);
}

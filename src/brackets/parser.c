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

int	p(t_list *el, void *cmp_str)
{
  t_data	*content;

  content = el->content;
  if (content && content->type == 's')
      return (ft_strcmp(content->data.string, cmp_str) == 0);
  return (0);
}

void	argument(char **tokens, char *arg_rules)
{
  t_array	*array;
  int		ivalue;
  float		fvalue;
  char		**cpy;
  
  cpy = tokens;
  array = array_new(sizeof(float), 8);
  while (*arg_rules)
    {
      if (!*tokens)
	{printf("not enough args for :"); return ;}
      if (*arg_rules == 'i')
  	{
  	  ivalue = ft_atoi(*tokens);
  	  array_add(array, &ivalue, sizeof(int));
  	}
      if (*arg_rules == 'f')
  	{
  	  fvalue = ft_atof(*tokens);
  	  array_add(array, &fvalue, sizeof(float));
  	}
      ++tokens;
      ++arg_rules;
    }
  ft_free_strsplit(cpy);
  return (array);
}

typedef struct	s_obj{
  char		*type;
  t_list        props;
}		t_obj;

void	parse(t_list *rules, t_list *config, int level)
{
  t_data	*content_rules;
  t_data	*content_config;
  t_list	*match;

  match = 0;
  while (config)
    {
      content_config = config->content;
      if (content_config)
	{
	  if (content_config->type == 's')
	    {
	      if (!config->next)
		{
		  content_rules = rules->content;
		  argument(ft_strsplit(content_config->data.string, ' '),
			   content_rules->data.string);		
		}
	      match = (ft_lstfind(rules, p, content_config->data.string));
	      if (!match)
		printf("error with %s\n", content_config->data.string);
	    }
	  else if (match && content_config->type == 'l')
	    {
	      content_rules = match->next->content;
	      parse(content_rules->data.list, content_config->data.list, level + 1); 
	    }
	}
      config = config->next;
    }
}

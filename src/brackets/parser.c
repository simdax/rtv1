#include "parser.h"
#include "object.h"

int	is_keyword(t_list *el, void *cmp_str)
{
  t_data	*content;

  content = el->content;
  if (content && content->type == 's')
      return (ft_strcmp(content->data.string, cmp_str) == 0);
  return (0);
}

t_array	*argument(char **tokens, char *arg_rules)
{
  t_array	*array;
  int		ivalue;
  float		fvalue;
  char		**cpy;

  cpy = tokens;
  array = array_new(1, 8);
  while (*arg_rules)
    {
      if (!*tokens)
	{printf("not enough args for :"); return(0) ;}
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

void	*factory(int new, t_list **objects, t_envir *envir, t_array *props)
{
  t_obj obj;

  if (new)
    {
      obj = object_new(envir->namespace, envir->parent);
      ft_lstadd(objects, ft_lstnew(&obj, sizeof(t_obj)));
      return (0);
    }
  else
    {
      object_set((*objects)->content, envir->namespace, envir->parent, props->mem);
      array_free(props);
      return (0);
    }
}

void	record_name(t_list *rules, t_list *config,
		    t_list **objects, t_list **match, t_envir *envir)
{
  t_data	*content_rules;
  t_data	*content_config;
  
  content_config = config->content;
  if (!config->next && *objects)
    {
      content_rules = rules->content;
      factory(0, objects, envir, argument(ft_strsplit(content_config->data.string, ' '), 
				  content_rules->data.string));
    }
  else 
    {
      if ((*match = (ft_lstfind(rules, is_keyword, content_config->data.string))))
	{
	  if (ft_strequ(envir->namespace, "objects"))
	    factory(1, objects, &((t_envir){content_config->data.string,
		    0, 0, envir->namespace}), 0);
	}
      else
	printf("error with %s for %s\n",
	       content_config->data.string, envir->namespace);
    }	     
}

void	parse(t_list *rules, t_list *config, t_list **objects, t_envir *envir)
{
  t_data	*content_rules;
  t_data	*content_config;
  t_list	*match;
  t_obj		*object;
  
  match = 0;
  while (config)
    {
      content_config = config->content;
      if (content_config)
	{
	  if (content_config->type == 's')
	    record_name(rules, config, objects, &match, envir);
	  else if (match && content_config->type == 'l')
	    {
	      content_rules = match->next->content;
	      parse(content_rules->data.list, content_config->data.list, objects,
		    &((t_envir){((t_data*)match->content)->data.string,
			  content_rules->data.list, content_config->data.list,
			  envir->namespace
			  })); 
	    }
	}
      config = config->next;
    }
}

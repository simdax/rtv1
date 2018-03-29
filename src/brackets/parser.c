#include "parser.h"
#include "object.h"
#include "globals.h"

static int	is_keyword(t_list *el, void *cmp_str)
{
  t_data	*content;

  content = el->content;
  if (content && content->type == 's')
      return (ft_strcmp(content->data.string, cmp_str) == 0);
  return (0);
}

static t_array	*argument(char **tokens, char *arg_rules)
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

static void	factory(int new, t_envir *envir, t_array *props)
{
  t_obj obj;

  if (new)
    {
      obj = object_new(envir->namespace, envir->parent);
      ft_lstadd(envir->objects, ft_lstnew(&obj, sizeof(t_obj)));
    }
  else 
    {
      if (envir->current == 1)
	object_set((*envir->objects)->content, envir->namespace,
      		     envir->parent, props->mem);
      if (envir->current == 2)
      	globals_set(envir->globals, envir->namespace,
      		    envir->parent, props->mem);
      array_free(props);
    }
}

static void	write_mem(t_list *rules, t_list *config,
		      t_list **match, t_envir envir)
{
  t_data	*content_rules;
  t_data	*content_config;

  content_config = config->content;
  if (!config->next && *(envir.objects))
    {
      content_rules = rules->content;
      factory(0, &envir, argument(ft_strsplit(content_config->data.string, ' '),
		content_rules->data.string));
    }
  else
    {
      if ((*match = (ft_lstfind(rules, is_keyword,
				content_config->data.string))))
	{
	  if (ft_strequ(envir.namespace, "objects"))
	    {
	      envir.namespace = content_config->data.string;
	      factory(1, &envir, 0);
	    }
	}
      else
	printf("error with %s for %s\n",
	       content_config->data.string, envir.namespace);
    }
}

static void	branching(t_list *rules, t_data *config, t_envir envir)
{
  envir.parent = envir.namespace;
  envir.namespace = ((t_data*)rules->content)->data.string;
  envir.rules = ((t_data*)rules->next->content)->data.list;
  envir.config = config->data.list;
  if (ft_strequ(envir.namespace, "objects"))
    envir.current = 1;
  else if (ft_strequ(envir.namespace, "global"))
    envir.current = 2;
  parse(envir);
}

void		parse(t_envir envir)
{
  t_data	*content_config;
  t_list	*match;
  
  match = 0;
  while (envir.config)
    {
      content_config = envir.config->content;
      if (content_config)
	{
	  if (content_config->type == 's')
	    write_mem(envir.rules, envir.config, &match, envir);
	  else if (match && content_config->type == 'l')
	    branching(match, content_config, envir);
	}
      envir.config = envir.config->next;
    }
}

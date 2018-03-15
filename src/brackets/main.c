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
    {
      printf("dafsd %s \n", content->data.string); 
      /* printf("%d", ft_strcmp(content->data.string, cmp_str)); */
      /* fflush(stdout); */
      return (ft_strcmp(content->data.string, cmp_str) == 0);
    }
  return (0);
}

void	go(t_list *rules, t_list *config, int level)
{
  //  t_data	*content_rules;
  t_data	*content_config;
  t_list	*match;

  match = 0;
  //  content_rules = rules->content;
  pprint(rules, 0); 
  while (config)
    {
      content_config = config->content;
      if (content_config)
	{
	  if (content_config->type == 's')
	    match = (ft_lstfind(rules, p, content_config->data.string));
	  //	  printf("%s\n", match ? /* ((t_data*)match->content)->data.string */ "fd ": "fdas");
	  if (match && content_config->type == 'l')
	    go(((t_data*)match->next->content)->data.list, content_config->data.list, level + 1); 
	}
      config = config->next;
    }
}

int	main(int argc, char **argv)
{
  char		*txt_rules;
  char		*txt_config;
  t_list	*rules;
  t_list	*config;

  txt_rules = get_file_content("rules");
  txt_config = get_file_content("config");
  //printf("%s", txt_config);
  config = parse(&txt_config);
  rules = parse(&txt_rules);
  go(rules, config, 0);
  /* free(txt_rules); */
  /* free(txt_config); */
  //  tree = go(tmp_tree);
}

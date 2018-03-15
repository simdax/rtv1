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

void	go(t_list *rules, t_list *config, int level)
{
  t_data	*content_rules;
  t_data	*content_config;

  printf("fdsafds"); fflush(stdout);
  while (config)
    {
      content_rules = rules->content;
      content_config = config->content;
      if (content_config)
	{
	  if (content_config->type == 's' && content_rules->data.string)
	    {
	      printf("%d : %s\n", level, content_config->data.string);
	      printf("%d : %s\n", level, content_rules->data.string);
	    }
	}
      if (content_config->type == 'l' && content_rules->data.list)
	go(content_config->data.list, content_rules->data.list, level + 1);
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
  printf("%s\n", txt_config); fflush(stdout);
  config = parse(&txt_config);
  ft_lstiter(config, ft_lstprint);
  pprint(config, 0);
  //  rules = parse(&txt_rules);
    //go(rules, config, 0);
  /* free(txt_rules); */
  /* free(txt_config); */
  //  tree = go(tmp_tree);
}

#include "libft.h"
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

void	po(t_list *el)
{
  t_obj	*obj;

  obj = (t_obj*)el->content;
  if (obj)
    object_print(obj);
}

void	del_object(void *c, size_t size)
{
  t_obj		*content;

  content = c;
  if (content)
    {
      free(content->tag);
      free(content->obj.sphere);
    }
  free(content);  
}

int	main()
{
  char		*txt_rules;
  char		*txt_config;
  t_list	*rules;
  t_list	*config;
  t_list	*objects;

  objects = 0;
  txt_rules = get_file_content("rules");
  txt_config = get_file_content("config");
  config = lex(txt_config);
  rules = lex(txt_rules);
   pprint(rules, 0);
   pprint(config, 0);     
  //  ft_lstiter(rules, p);
  //  parse(rules, config, &objects, &((t_envir){0, rules, config, 0}));
  free(txt_rules);
  free(txt_config);
  ft_lstdel(&rules, del_data);
  ft_lstdel(&config, del_data);
  //  ft_lstdel(&objects, del_object);
}
#include "parser.h"

void	po(t_list *el)
{
  printf("type : %s\n", ((t_obj*)el->content)->tag);
  vec3f_print(((t_obj*)el->content)->obj.sphere->center);
  vec3f_print(((t_obj*)el->content)->obj.sphere->surface_color);
}

int	main(int argc, char **argv)
{
  char		*txt_rules;
  char		*txt_config;
  t_list	*rules;
  t_list	*config;
  t_list	*objects = 0;

  txt_rules = get_file_content("rules");
  txt_config = get_file_content("config");
  config = lex(&txt_config);
  rules = lex(&txt_rules);
  parse(rules, config, &objects, &((t_envir){0, rules, config, 0}));
  ft_lstiter(objects, po);
  /* free(txt_rules); */
  /* free(txt_config); */
  //  tree = go(tmp_tree);
}

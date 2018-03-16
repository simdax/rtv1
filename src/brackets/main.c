#include "parser.h"

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
  ft_lstprint(objects);
  /* free(txt_rules); */
  /* free(txt_config); */
  //  tree = go(tmp_tree);
}

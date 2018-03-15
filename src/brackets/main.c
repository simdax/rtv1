#include "parser.h"

int	main(int argc, char **argv)
{
  char		*txt_rules;
  char		*txt_config;
  t_list	*rules;
  t_list	*config;

  txt_rules = get_file_content("rules");
  txt_config = get_file_content("config");
  //printf("%s", txt_config);
  config = lex(&txt_config);
  rules = lex(&txt_rules);
  parse(rules, config, 0);
  /* free(txt_rules); */
  /* free(txt_config); */
  //  tree = go(tmp_tree);
}

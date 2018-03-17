#include "parser.h"

t_list	*read_configuration(char *config_file, char *rules_file)
{
  char		*txt_rules;
  char		*txt_config;
  t_list	*rules;
  t_list	*config;
  t_list	*objects;

  objects = 0;
  txt_rules = get_file_content(rules_file);
  txt_config = get_file_content(config_file);
  config = lex(txt_config);
  rules = lex(txt_rules);
  parse(rules, config, &objects, &((t_envir){0, rules, config, 0}));
  //print();//  ft_lstiter(objects, po);
  free(txt_rules);
  free(txt_config);
  return (objects);
}

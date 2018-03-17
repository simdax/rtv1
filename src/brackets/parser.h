#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "object.h"

typedef struct	s_data{
  char		type;
  union 	u_data{
    char	*string;
    t_list	*list;    
  }		data;
}		t_data;

typedef struct	s_envir{
  char		*namespace;
  t_list	*rules;
  t_list	*config;
  char		*parent;
}		t_envir;

t_data		*new_data(char type, void *d);
//t_list		*go(char *buf);
char		*get_file_content(char *path);
t_list		*lex(char *buf);
void		parse(t_list *rules, t_list *config, t_list **objects, t_envir *envir);
t_list		*read_configuration(char *config_file, char *rules_file);

#endif

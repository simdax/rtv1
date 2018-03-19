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
t_data		new_data2(char type, void *d);
void		del_data(void *c, size_t size);
t_list		*lex(char *buf);
void		parse(t_list *rules, t_list *config,
		      t_list **objects, t_envir *envir);
t_list		*read_configuration(char *config_file, char *rules_file);

#endif

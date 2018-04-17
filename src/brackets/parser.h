/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 19:29:57 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/17 13:15:44 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "srcs/types/errors.h"
# include "srcs/types/data.h"
# include "object.h"
# include "globals.h"
# include "array.h"

typedef struct	s_envir{
	char		*namespace;
	t_list		*rules;
	t_list		*config;
	char		*parent;
	int			current;
	t_list		**objects;
	t_globals	*globals;
	t_array		*bug;
}				t_envir;

typedef struct	s_conf{
	t_list		*tmp_objects;
	t_obj		**objects;
	t_globals	globals;
}				t_conf;

void			conf_free(t_conf *conf);
void			print_objects(t_list *el);
void			print_error(void *el, t_array *array);
int				is_keyword(t_list *el, void *cmp_str);
t_list			*lex(char *buf);
void			parse(t_envir envir);
void			error();
t_conf			*read_configuration(char *config_file, char *rules_file);
int				begin_parse(char *txt_rules, char *txt_config,
					t_list **objects, t_globals *globals);

#endif

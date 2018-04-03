/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 16:49:35 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/03 16:49:35 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "object.h"

typedef struct	s_data{
	char			type;
	union		u_data{
		char	*string;
		t_list	*list;
	}				data;
}				t_data;

typedef struct	s_globals{
	int		width;
	int		height;
	t_vec3f	from;
	t_vec3f	to;
}				t_globals;

typedef struct	s_envir{
	char		*namespace;
	t_list		*rules;
	t_list		*config;
	char		*parent;
	int			current;
	t_list		**objects;
	t_globals	*globals;
}				t_envir;

typedef struct	s_conf{
	t_list		*tmp_objects;
	t_obj		**objects;
	t_globals	globals;
}				t_conf;

int				is_keyword(t_list *el, void *cmp_str);
t_data			*new_data(char type, void *d);
t_data			new_data2(char type, void *d);
void			del_data(void *c, size_t size);
t_list			*lex(char *buf);
void			parse(t_envir envir);
t_conf			*read_configuration(char *config_file, char *rules_file);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:30:44 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/17 17:32:01 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_TYPES_H
# define PARSER_TYPES_H

# include "globals.h"
# include "object.h"

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

#endif

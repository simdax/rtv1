/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:25:42 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/03 12:45:35 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "globals.h"

static void	po(t_list *el)
{
	t_obj	*obj;

	obj = (t_obj*)el->content;
	if (obj)
		object_print(obj);
}

t_list	*read_configuration(char *config_file, char *rules_file)
{
	char		*txt_rules;
	char		*txt_config;
	t_list		*rules;
	t_list		*config;
	t_conf		*conf;
	t_list		*objects;
	t_globals	globals;

	conf = malloc(sizeof(t_conf));
	objects = 0;
	globals = (t_globals){640, 480, {0, 0, 0}, {0, 0, 0}};
	txt_rules = get_file_content(rules_file);
	txt_config = get_file_content(config_file);
	config = lex(txt_config);
	rules = lex(txt_rules);
	parse((t_envir){0, rules, config, 0, 0, &objects, &globals});
	ft_lstiter(objects, po);
	globals_print(&globals);
	free(txt_rules);
	free(txt_config);
	return (objects);
}

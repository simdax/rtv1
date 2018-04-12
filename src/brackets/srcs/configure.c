/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:25:14 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/12 20:40:28 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "globals.h"
#include "libft.h"

void		cpy(t_list *elem, void *arg)
{
	t_obj	***objects;

	objects = arg;
	**objects = ((t_obj*)elem->content);
	(*objects)++;
}

t_obj		**to_array(t_list *o)
{
	t_obj	**objects;
	t_obj	**copy;
	int		size;

	size = ft_lstsize(o);
	objects = malloc(sizeof(t_obj*) * (size + 1));
	copy = objects;
	ft_lstiter2(o, cpy, &copy);
	objects[size] = 0;
	return (objects);
}

static void	po(t_list *el)
{
	t_obj	*obj;

	obj = (t_obj*)el->content;
	if (obj)
		object_print(obj);
}

t_conf		*read_configuration(char *config_file, char *rules_file)
{
	char		*txt_rules;
	char		*txt_config;
	t_list		*rules;
	t_list		*config;
	t_conf		*conf;

	printf("\nParsing\n");
	conf = malloc(sizeof(t_conf));
	conf->tmp_objects = 0;
	conf->globals = (t_globals){640, 480, {0, 0, 0}, {0, 0, -1}};
	txt_rules = get_file_content(rules_file);
	txt_config = get_file_content(config_file);
	if(!(begin_parse(txt_rules, txt_config, &conf->tmp_objects, &conf->globals)))
	{
		ft_lstiter(conf->tmp_objects, print_objects);
		globals_print(&conf->globals);			
	}
	free(txt_rules);
	free(txt_config);
	conf->objects = to_array(conf->tmp_objects);
	return (conf);
}

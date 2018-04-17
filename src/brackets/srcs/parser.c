/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:36:02 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/17 16:41:02 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "object.h"
#include "globals.h"

static t_array	*arg(char **tokens, char *arg_rules)
{
	t_array	*array;
	int		ivalue;
	float	fvalue;
	int		i;

	i = 0;
	array = array_new(1, 8);
	while (arg_rules[i] && tokens[i])
	{
		if (arg_rules[i] == 'i')
		{
			ivalue = ft_atoi(tokens[i]);
			array_add(array, &ivalue, sizeof(int));
		}
		else if (arg_rules[i] == 'f')
		{
			fvalue = ft_atof(tokens[i]);
			array_add(array, &fvalue, sizeof(float));
		}
		++i;
	}
	if (array->cursor < ft_strlen(arg_rules))
		array_free3(&array);
	ft_free_strsplit(tokens);
	return (array);
}

static void		factory(int new, t_envir *envir, t_array *props)
{
	t_obj obj;

	if (new)
	{
		obj = object_new(envir->namespace, envir->parent);
		ft_lstadd(envir->objects, ft_lstnew(&obj, sizeof(t_obj)));
	}
	else if (props)
	{
		if (envir->current == 1)
			object_set((*envir->objects)->content, envir->namespace,
					envir->parent, props->mem);
		if (envir->current == 2)
			globals_set(envir->globals, envir->namespace,
						envir->parent, props->mem);
		array_free(props);
	}
	else
		error_new(envir->namespace, envir->parent, envir->bug, 1);
}

static void		write_mem(t_list *r, t_list *c, t_list **match, t_envir envir)
{
	t_data	*rules;
	t_data	*cnf;

	cnf = c->content;
	if (!c->next && *(envir.objects))
	{
		rules = r->content;
		factory(0, &envir, arg(ft_strsplit(cnf->data.string, ' '),
							rules->data.string));
	}
	else
	{
		if ((*match = (ft_lstfind(r, is_keyword,
								cnf->data.string))))
		{
			if (ft_strequ(envir.namespace, "objects"))
			{
				envir.namespace = cnf->data.string;
				factory(1, &envir, 0);
			}
		}
		else
			error_new(cnf->data.string, envir.namespace, envir.bug, 0);
	}
}

static void		branching(t_list *rules, t_data *config, t_envir envir)
{
	envir.parent = envir.namespace;
	envir.namespace = ((t_data*)rules->content)->data.string;
	envir.rules = ((t_data*)rules->next->content)->data.list;
	envir.config = config->data.list;
	if (ft_strequ(envir.namespace, "objects"))
		envir.current = 1;
	else if (ft_strequ(envir.namespace, "global"))
		envir.current = 2;
	parse(envir);
}

void			parse(t_envir envir)
{
	t_data	*content_config;
	t_list	*match;

	match = 0;
	while (envir.config)
	{
		content_config = envir.config->content;
		if (content_config)
		{
			if (content_config->type == 's')
				write_mem(envir.rules, envir.config, &match, envir);
			else if (match && content_config->type == 'l')
				branching(match, content_config, envir);
		}
		envir.config = envir.config->next;
	}
}

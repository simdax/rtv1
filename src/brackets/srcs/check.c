/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 11:24:01 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/12 20:29:09 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "globals.h"

/* void	pprint(t_list *list, int level) */
/* { */
/* 	t_data	*content; */

/* 	while (list) */
/* 	{ */
/* 		content = list->content; */
/* 		if (content) */
/* 		{ */
/* 			if (content->type == 's') */
/* 				printf("%d : %s\n", level, content->data.string); */
/* 			if (content->type == 'l') */
/* 				pprint(content->data.list, level + 1); */
/* 		} */
/* 		list = list->next; */
/* 	} */
/* } */

int			begin_parse(char *txt_rules, char *txt_config, t_list **objects,
						t_globals *globals)
{
	t_envir		envir;
	t_list		*rules;
	t_list		*config;
	t_array		*bugs;

	bugs = array_new(1, 4);
	config = lex(txt_config);
	if (!config)
	{
		ft_lstdel(&config, del_data);
		return (0);
	}
	rules = lex(txt_rules);
	envir = (t_envir){0, rules, config, 0, 0, objects, globals, bugs};
	parse(envir);
	array_for_each(bugs, print_error);
	array_free(bugs);
	return (bugs->cursor);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 21:11:32 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/17 18:35:31 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "globals.h"
#include "printf.h"

void		pprint(t_list *list, int level)
{
	t_data	*content;

	while (list)
	{
		content = list->content;
		if (content)
		{
			if (content->type == 's')
				ft_printf("%d : %s\n", level, content->data.string);
			if (content->type == 'l')
				pprint(content->data.list, level + 1);
		}
		list = list->next;
	}
}

int			begin_parse(char *txt_rules, char *txt_config, t_list **objects,
						t_globals *globals)
{
	t_envir		envir;
	t_list		*rules;
	t_list		*config;
	t_array		*bugs;
	int			ret;

	config = lex(txt_config);
	if (!config)
		return (-1);
	bugs = array_new(sizeof(t_error), 4);
	rules = lex(txt_rules);
	envir = (t_envir){0, rules, config, 0, 0, objects, globals, bugs};
	parse(envir);
	array_for_each(bugs, error_print);
	ret = bugs->cursor;
	array_free(bugs);
	ft_lstdel(&rules, del_data);
	ft_lstdel(&config, del_data);
	return (ret);
}

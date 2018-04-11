/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_valgrind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:07:24 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/11 12:39:41 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "globals.h"

void	pprint(t_list *list, int level)
{
	t_data	*content;

	while (list)
	{
		content = list->content;
		if (content)
		{
			if (content->type == 's')
				printf("%d : %s\n", level, content->data.string);
			if (content->type == 'l')
				pprint(content->data.list, level + 1);
		}
		list = list->next;
	}
}

void	po(t_list *el)
{
	t_obj	*obj;

	obj = (t_obj*)el->content;
	if (obj)
		object_print(obj);
}

void	go(char *path)
{
	char		*txt_rules;
	char		*txt_config;
	t_list		*rules;
	t_list		*config;
	t_list		*objects;
  t_globals globals;
  
	objects = 0;
	globals = (t_globals){640, 480, {0, 0, 0}, {0, 0, 0}};
	txt_rules = get_file_content("rules");
	txt_config = get_file_content(path);
	config = lex(txt_config);
	rules = lex(txt_rules);
  if (!config)
      return ;
	parse((t_envir){0, rules, config, 0, 0, &objects, &globals});
	ft_lstiter(objects, po);
	globals_print(&globals);
	free(txt_rules);
	free(txt_config);
	ft_lstdel(&rules, del_data);
	ft_lstdel(&config, del_data);
	ft_lstdel(&objects, object_del);
}

int		main(void)
{
	go("test/config");
  go("test/config_false");
}

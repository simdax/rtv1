/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 11:24:01 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/12 11:54:44 by scornaz          ###   ########.fr       */
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

void	check(t_list *objects, t_globals *globals, t_list *rules, t_list *config)
{
		ft_lstiter(objects, po);
		globals_print(globals);
		ft_lstdel(&rules, del_data);
		ft_lstdel(&config, del_data);
		ft_lstdel(&objects, object_del);
}

int		begin_parse(char *txt_rules, char *txt_config, t_list **objects,
					t_globals *globals)
{
		t_envir		envir;
		t_list		*rules;
		t_list		*config;
		t_array		*bugs;
		static char			*errors[2] = {
				0, "erreur mec"
		};
		
		bugs = array_new(1, 4);
		config = lex(txt_config);
		rules = lex(txt_rules);
		envir = (t_envir){0, rules, config, 0, 0, objects, globals, bugs};
		if (!config)
		{
				printf("pas de fichier configuration valide\n");
				return (0);
		}
		parse(envir);
		while (bugs->mem && bugs->cursor--)
				if (((char*)bugs->mem)[bugs->cursor])
						printf("error : %s\n", errors[((char*)bugs->mem)[bugs->cursor]]);
		array_free(bugs);
		check(*objects, globals, config, rules);
		return (1);
}

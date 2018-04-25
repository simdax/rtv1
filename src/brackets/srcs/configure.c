/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:40:57 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/25 15:36:46 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "globals.h"
#include "printf.h"
#include "get_next_line.h"

void			print_obj(t_obj **objs)
{
		int o = 0;
		while (*objs)
		{
				printf("dsfd %d", o);
				while (*objs)
				{
						object_print(*objs);
						++objs;
						++o;
				}
				++o;
				++objs;
		}
}

void				cpy(t_list *elem, int i, void *a)
{
		t_obj				***objects;
		int				**count;
		t_bof	*arg;

		arg = a;
		objects = arg->obj;
		count = arg->count;
		printf("%d\n", i);
		if (*count && **count == i)
		{
				printf("cut at %d\n", i);
				**objects = 0;
				(*objects)++;
				(*count)++;
		}
		**objects = ((t_obj*)elem->content);
		(*objects)++;
}

void				mins(void *a, void *b)
{
		*(int*)a = *(int*)a - *(int*)b;
}

t_obj				**to_array(t_list *o, t_array	*count)
{
		t_obj	**objects;
		t_obj	**copy;
		int		size;

		size = ft_lstsize(o) + count->cursor + 1;
		objects = malloc(sizeof(t_obj*) * (size + 1));
		copy = objects;
		array_reverse(count);
		array_reduce(count, mins);
		ft_lstiter3(o, cpy, &(t_bof){&copy, (int**)(&count->mem)});
		objects[size] = 0;
		objects[size + 1] = 0;
		return (objects);
}

static void	free_conf(t_conf **conf)
{
		free(*conf);
		*conf = 0;
}

t_conf			*read_configuration(char *config_file, char *rules_file)
{
		char		*txt_rules;
		char		*txt_config;
		t_conf	*conf;

		ft_printf("\nParsing\n");
		conf = malloc(sizeof(t_conf));
		conf->tmp_objects = 0;
		conf->objects = 0;
		conf->globals = (t_globals){640, 480, {0, 0, 0}, {0, 0, -1}};
		txt_rules = get_file_content(rules_file);
		txt_config = get_file_comment(config_file, '#');
		ft_printf("%s\n", txt_config);
		if (!(begin_parse(txt_rules, txt_config, conf)))
		{
//				ft_lstiter(conf->tmp_objects, print_objects);
				globals_print(&conf->globals);
				conf->objects = to_array(conf->tmp_objects, conf->num);
				print_obj(conf->objects);
		}
		else
				free_conf(&conf);
		free(txt_rules);
		free(txt_config);
		return (conf);
}

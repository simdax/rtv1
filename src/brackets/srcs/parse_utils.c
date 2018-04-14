/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 11:12:36 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/14 14:18:47 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "object.h"
#include "globals.h"
#include "printf.h"

int		is_keyword(t_list *el, void *cmp_str)
{
	t_data	*content;

	content = el->content;
	if (content && content->type == 's')
		return (ft_strcmp(content->data.string, cmp_str) == 0);
	return (0);
}

void	error(t_data *config, char *namespace, t_array *bug)
{
	int	error_code;

	error_code = 1;
	ft_printf("error with '%s' for %s\n",
			config->data.string, namespace);
	array_add(bug, &error_code, 1);
}

void	print_objects(t_list *el)
{
	t_obj	*obj;

	obj = (t_obj*)el->content;
	if (obj)
		object_print(obj);
}

void	print_error(void *el, t_array *array)
{
	static char			*errors[2] = {
		0, "erreur mec"
	};

	ft_printf("error : %s\n", errors[*(char*)el]);
}

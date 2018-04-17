/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 11:12:36 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/17 13:12:30 by scornaz          ###   ########.fr       */
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

void	print_objects(t_list *el)
{
	t_obj	*obj;

	obj = (t_obj*)el->content;
	if (obj)
		object_print(obj);
}

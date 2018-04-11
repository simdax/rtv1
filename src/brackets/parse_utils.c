/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:05:54 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/11 15:12:18 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "object.h"
#include "globals.h"

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
    printf("error with '%s' for %s\n",
           config->data.string, namespace);
    array_add(bug, &error_code, 1);
}

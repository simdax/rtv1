/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 12:48:08 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/17 16:43:16 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "printf.h"

void	error_new(char *namespace, char *parent, t_array *bugs, int err)
{
	t_error	error;

	error.code = err;
	error.namespace = namespace;
	error.parent = parent;
	array_add(bugs, &error, 1);
}

void	error_print(void *el, t_array *array)
{
	t_error			*error;
	static char		*error_msgs[] = {
		"no match", "not enough arg"
	};
	static char		*help_msgs[] = {
		"check your rule file", "check your config file"
	};

	error = el;
	ft_printf("error : %s for %s in %s\nyou should %s\n",
			error_msgs[error->code], error->namespace, error->parent,
			help_msgs[error->code]);
}

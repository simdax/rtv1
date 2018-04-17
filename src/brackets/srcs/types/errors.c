/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 12:48:08 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/17 18:45:56 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "parser_types.h"
#include "errors.h"

void	error_new(t_envir *envir, int err)
{
	t_error	error;

	error.code = err;
	error.namespace = envir->namespace;
	error.parent = envir->parent;
	array_add(envir->bug, &error, 1);
}

void	error_print(void *el, t_array *array)
{
	t_error			*error;
	static char		*error_msgs[] = {
		"no match", "not enough arg", "bad argument"
	};
	static char		*help_msgs[] = {
		"check your rule file", "check your config file",
		"check carefully your file"
	};
	error = el;
	ft_printf("Error : %s for %s in %s\nYou should %s\n",
			error_msgs[error->code], error->namespace,
			error->parent ? "global" : error->parent,
			help_msgs[error->code]);
}

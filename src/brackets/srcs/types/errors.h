/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 12:48:14 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/17 16:41:26 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "array.h"
# include "data.h"

typedef struct	s_error {
	int		code;
	int		line;
	char	*namespace;
	char	*parent;
}				t_error;

void			error_new(char *namespace, char *parent,
					t_array *bugs, int error);
void			error_print(void *el, t_array *array);

#endif

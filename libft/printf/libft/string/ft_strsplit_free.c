/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:48:31 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/17 12:02:10 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_strsplit(char **str)
{
	char	**cpy;

	cpy = str;
	while (*str)
		free(*str++);
	free(cpy);
	cpy = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valgrind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 20:11:30 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/13 14:54:54 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "globals.h"

int		main(void)
{
//	conf_free(read_configuration("test/config", "rules"));
	conf_free(read_configuration("test/config_false", "rules"));
//	conf_free(read_configuration("test/config_false2", "rules"));
//	conf_free(read_configuration("test/config_false3", "rules"));		 
}

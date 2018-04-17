/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valgrind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 20:11:30 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/17 16:44:05 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "globals.h"

int		main(void)
{
	conf_free(read_configuration("test/sujet/dur", "test/rules"));
	conf_free(read_configuration("test/config", "test/rules"));
	conf_free(read_configuration("test/config_false", "test/rules"));
	conf_free(read_configuration("test/config_false2", "test/rules"));
	conf_free(read_configuration("test/config_false3", "test/rules"));
	conf_free(read_configuration("test/config_false4", "rules"));
}

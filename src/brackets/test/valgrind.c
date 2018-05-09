/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valgrind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 20:11:30 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/09 13:25:15 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "globals.h"

void	conf_free(t_conf *conf)
{
	if (!conf)
		return ;
	ft_lstdel(&conf->tmp_objects, object_del);
	free(conf->objects);
	free(conf);
}

int		main(void)
{
	conf_free(read_configuration("test/sujet/mul", "test/rules"));
	conf_free(read_configuration("test/sujet/dur", "test/rules"));
	conf_free(read_configuration("test/config", "test/rules"));
	conf_free(read_configuration("test/config_false", "test/rules"));
	conf_free(read_configuration("test/config_false2", "test/rules"));
	conf_free(read_configuration("test/config_false3", "test/rules"));
	conf_free(read_configuration("test/config_false4", "test/rules"));
}

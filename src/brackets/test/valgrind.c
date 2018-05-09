/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valgrind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 20:11:30 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/09 16:19:35 by scornaz          ###   ########.fr       */
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
		conf_free(read_configuration("../../configs/config2", "test/rules"));
		conf_free(read_configuration("", "test/rules"));
		conf_free(read_configuration("test/sujet/mul", "test/rules"));
		conf_free(read_configuration("test/sujet/dur", "test/rules"));
		conf_free(read_configuration("test/config", "test/rules"));
		conf_free(read_configuration("test/config_false", "test/rules"));
		conf_free(read_configuration("test/config_false2", "test/rules"));
		conf_free(read_configuration("test/config_false3", "test/rules"));
		conf_free(read_configuration("test/config_false4", "test/rules"));
		conf_free(read_configuration("test/configs/config", "test/rules"));
		conf_free(read_configuration("test/configs/config2", "test/rules"));
		conf_free(read_configuration("test/configs/config3", "test/rules"));
		conf_free(read_configuration("test/configs/config4", "test/rules"));
		conf_free(read_configuration("test/configs/config5", "test/rules"));
		conf_free(read_configuration("test/configs/config6", "test/rules"));
}

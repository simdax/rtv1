/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valgrind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 20:11:30 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/12 20:40:41 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "globals.h"

int		main(void)
{
		read_configuration("test/config", "rules");
		read_configuration("test/config_false", "rules");
		read_configuration("test/config_false2", "rules");
		read_configuration("test/config_false3", "rules");		 
}

/* ************************************************************************** */
/*																																						*/
/*																												:::			 ::::::::		*/
/*	 test_valgrind.c																		:+:			 :+:		:+:		*/
/*																										+:+ +:+					+:+			*/
/*	 By: scornaz <marvin@42.fr>											+#+	 +:+			 +#+				*/
/*																								+#+#+#+#+#+		+#+						*/
/*	 Created: 2018/04/03 14:07:24 by scornaz					 #+#		#+#							*/
/*   Updated: 2018/04/12 11:48:02 by scornaz          ###   ########.fr       */
/*																																						*/
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "globals.h"

void	go(char *path)
{
		char		*txt_rules;
		char		*txt_config;
		t_list		*objects;
		t_globals globals;
	
		printf("\nParsing\n");
		objects = 0;
		globals = (t_globals){640, 480, {0, 0, 0}, {0, 0, 0}};
		txt_rules = get_file_content("rules");
		txt_config = get_file_content(path);
		begin_parse(txt_rules, txt_config, &objects, &globals);
		free(txt_rules);
		free(txt_config);
}

int		main(void)
{
		go("test/config");
		go("test/config_false");
		go("test/config_false2");		 
}

/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 api2.c												:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: scornaz <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2018/04/16 12:37:15 by scornaz		   #+#	  #+#			  */
/*   Updated: 2018/04/16 14:27:40 by scornaz          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "websocket.h"

int i = 1;

void	sig_handler(int signo)
{
	printf("quitting");
	i = 0;
}

int main()
{
	t_ws_data	data;

	data.val = 17;
	data.running = 1;
	websocket_server(&data);
	// Continue main
	while (i)
	{
		signal(SIGINT, sig_handler);
		printf("val : %d\n", data.val);
		fflush(stdout);
		sleep(1);
	}
	return 0;
}

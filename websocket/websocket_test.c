/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   websocket_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:31:46 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/16 14:35:06 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "websocket.h"
#include <unistd.h>

int g_i = 1;

void	sig_handler(int signo)
{
	printf("quitting");
	g_i = 0;
}

int		main(void)
{
	t_ws_data	data;

	data.val = 17;
	websocket_server(&data);
	while (g_i)
	{
		signal(SIGINT, sig_handler);
		printf("val : %d\n", data.val);
		fflush(stdout);
		sleep(1);
	}
	return (0);
}

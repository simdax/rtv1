/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 12:37:15 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/16 14:00:45 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "websocket.h"
#include <stdio.h>

int i = 1;

void	sig_handler(int signo)
{
	printf("quitting");
	i = 0;
}

int	create_server(void *data)
{
	libwebsock_context *ctx = NULL;

	ctx = libwebsock_init(0, 0, 0);
	if(ctx == NULL) {
		fprintf(stderr, "Error during libwebsock_init.\n");
		return (1);
	}
	ctx->user_data = data;
	libwebsock_bind(ctx, "0.0.0.0", PORT);
	fprintf(stderr, "libwebsock listening on port %s\n", PORT);
	ctx->onmessage = onmessage;
	ctx->onopen = onopen;
	ctx->onclose = onclose;
	libwebsock_wait(ctx);
}

int main()
{
	pthread_t thread;
	int lock = 17;

	pthread_create(&thread, NULL, create_server, &lock);
	// Continue main
	while(i)
	{
		signal(SIGINT, sig_handler);
		printf("val : %d\n", lock);
		fflush(stdout);
		sleep(1);
	}
	return 0;
}

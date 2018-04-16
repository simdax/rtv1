/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   websocket_interface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:18:33 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/16 14:27:35 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "websocket.h"

int		create_server(void *data)
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

void	websocket_server(void *data)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, create_server, data);
}

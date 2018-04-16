/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 12:36:52 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/16 14:14:04 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "websocket.h"
#include "printf.h"

int	onmessage(libwebsock_client_state *state, libwebsock_message *msg)
{
	t_ws_data			*data_ptr;
	libwebsock_context	*ctx;

	fprintf(stderr, "Received message from client: %d\n", state->sockfd);
	fprintf(stderr, "Message opcode: %d\n", msg->opcode);
	fprintf(stderr, "Payload Length: %llu\n", msg->payload_len);
	fprintf(stderr, "Payload: %s\n", msg->payload);
	ctx = state->ctx;
	data_ptr = ctx->user_data;
	printf("%d\n", data_ptr->val);
	++(data_ptr->val);
	//now let's send it back.
	libwebsock_send_text(state, msg->payload);
	return 0;
}

int	onopen(libwebsock_client_state *state)
{
	fprintf(stderr, "connecting with id: %d\n", state->sockfd);
	return 0;
}

int	onclose(libwebsock_client_state *state)
{
	fprintf(stderr, "closing: %d\n", state->sockfd);
	return 0;
}

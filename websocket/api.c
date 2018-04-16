/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 12:36:52 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/16 14:01:48 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "websocket.h"

/*

  Define message callback with same prototype as below.
  Accepts pointer to libwebsock_client_state structure and pointer to libwebsock_message structure.
  libwebsock_client_state has int sockfd, struct sockaddr_storage *sa
  libwebsock_message has unsigned int opcode, unsigned long long payload_len, and char *payload

  You probably shouldn't modify any of the data contained in the structures passed to the callback.	 It will probably cause bad things to happen.
  You can, of course, make copies of the data contained therein.

  Here is the default receive_callback as an example:
  (libwebsock_send_text accepts libwebsock_client_state * and character array)

  int some_callback_name(libwebsock_client_state *state, libwebsock_message *msg) {
  libwebsock_send_text(state, msg->payload);
  return 0;
  }

  This callback just provides echoing messages back to the websocket client.

  You would register this callback via:

  ctx->onopen = some_callback_name;


*/


//basic onmessage callback, prints some information about this particular message
//then echos back to the client.
int onmessage(libwebsock_client_state *state, libwebsock_message *msg)
{
	int *data_ptr;
	libwebsock_context* ctx;

	fprintf(stderr, "Received message from client: %d\n", state->sockfd);
	fprintf(stderr, "Message opcode: %d\n", msg->opcode);
	fprintf(stderr, "Payload Length: %llu\n", msg->payload_len);
	fprintf(stderr, "Payload: %s\n", msg->payload);
	ctx = state->ctx;
	data_ptr = ctx->user_data;
	(*data_ptr)++;
	//now let's send it back.
	libwebsock_send_text(state, msg->payload);
	return 0;
}

int onopen(libwebsock_client_state *state)
{
	printf("coucou");
	fprintf(stderr, "onopen: %d\n", state->sockfd);
	return 0;
}

int onclose(libwebsock_client_state *state)
{
	fprintf(stderr, "onclose: %d\n", state->sockfd);
	return 0;
}

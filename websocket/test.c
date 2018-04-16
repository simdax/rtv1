#include <stdio.h>
#include <stdlib.h>
#include "libwebsock/src/websock.h"
#include <pthread.h>

/*

Define message callback with same prototype as below.
Accepts pointer to libwebsock_client_state structure and pointer to libwebsock_message structure.
libwebsock_client_state has int sockfd, struct sockaddr_storage *sa
libwebsock_message has unsigned int opcode, unsigned long long payload_len, and char *payload

You probably shouldn't modify any of the data contained in the structures passed to the callback.  It will probably cause bad things to happen.
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

#define PORT "5678"

int	create_server(void *data)
{
  libwebsock_context *ctx = NULL;
  ctx = libwebsock_init(0, 0, 0);
  if(ctx == NULL) {
    fprintf(stderr, "Error during libwebsock_init.\n");
    return(1);
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
  int i = 10;
  while(i)
    {
      printf("val : %d", lock);
      fflush(stdout);
      sleep(1);
      --i;
    }
  return 0;
}

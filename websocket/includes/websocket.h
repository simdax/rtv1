/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   websocket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:17:38 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/16 14:26:54 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSOCKET_H
# define WEBSOCKET_H

# define PORT "5678"
# include <signal.h>
# include <stdlib.h>
# include "websock.h"
# include <pthread.h>

typedef struct	s_ws_data{
	int val;
	int	running;
}				t_ws_data;

int				onmessage(libwebsock_client_state *state,
						libwebsock_message *msg);
int				onopen(libwebsock_client_state *state);
int				onclose(libwebsock_client_state *state);
void			websocket_server(void *data);

#endif

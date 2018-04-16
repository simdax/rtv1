/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   websocket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 12:41:31 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/16 14:01:51 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSOCKET_H
# define WEBSOCKET_H

# define PORT "5678"
# include <signal.h>
#include <stdlib.h>
#include "libwebsock/src/websock.h"
#include <pthread.h>

int onmessage(libwebsock_client_state *state, libwebsock_message *msg);
int onopen(libwebsock_client_state *state);
int onclose(libwebsock_client_state *state);

#endif

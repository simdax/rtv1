/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 05:37:09 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/10 16:34:33 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		*to_newscreen(void *param)
{
	t_launch	*launcher;

	launcher = param;
	launcher->state = NEW;
	return (NULL);
}

void		*to_mainscreen(void *param)
{
	t_launch	*launcher;

	launcher = param;
	launcher->state = MSCREEN;
	return (NULL);
}

void		*to_rtscreen(void *param)
{
	t_launch	*launcher;

	launcher = param;
	launcher->state = RTS;
	return (NULL);
}

void		*to_rtopt(void *param)
{
	t_rt	*opts;

	opts = param;
	opts->launcher->state = OPTS;
	rt_opts(opts);
	return (NULL);
}

void		*open_scn(void *param)
{
	t_thrprm	*event;

	event = param;
	through_argv(event);
	event->quited = 1;
	pthread_exit(NULL);
}

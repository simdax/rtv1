/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_fcon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:48:31 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/31 15:17:50 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "l_obj.h"

static void	angle(t_sdl *sdl, t_fcone2 *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_PLUS && obj->angle > 0.09)
		obj->angle -= 0.01;
	else if (sdl->event->key.keysym.sym == SDLK_KP_MINUS && obj->angle < 0.98)
		obj->angle += 0.01;
}

static void	con_axi(t_sdl *sdl, t_fcone2 *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_4)
	{
		obj->axis.x += 0.1;
		obj->axis.x >= 1.01 && \
		obj->axis.y <= 0.002 ? obj->axis.x = -0.7 : 0;
	}
	else if (sdl->event->key.keysym.sym == SDLK_KP_6)
	{
		obj->axis.x -= 0.1;
		obj->axis.x <= -1.01 && \
		obj->axis.y <= 0.002 ? obj->axis.x = 0.7 : 0;
	}
	else if (sdl->event->key.keysym.sym == SDLK_KP_7)
	{
		obj->axis.z -= 0.1;
		obj->axis.z <= -1.01 && \
		obj->axis.y <= 0.002 ? obj->axis.z = 0.7 : 0;
	}
	else if (sdl->event->key.keysym.sym == SDLK_KP_1)
	{
		obj->axis.z += 0.1;
		obj->axis.z >= 1.01 && \
		obj->axis.y <= 0.002 ? obj->axis.z = -0.7 : 0;
	}
}

static void	posi(t_sdl *sdl, t_fcone2 *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_DOWN)
		obj->tip_position.y -= 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_UP)
		obj->tip_position.y += 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_RIGHT)
		obj->tip_position.x += 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_LEFT)
		obj->tip_position.x -= 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_KP_5)
		obj->tip_position.z -= 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_KP_8)
		obj->tip_position.z += 0.2;
}

void		l_fcon(t_sdl *sdl, t_fcone2 *obj, t_obj *parent)
{
	(void)parent;
	angle(sdl, obj);
	con_axi(sdl, obj);
	posi(sdl, obj);
}

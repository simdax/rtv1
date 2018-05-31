/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_cone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:48:31 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/31 17:29:55 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "l_obj.h"

static void	angle(t_sdl *sdl, t_cone *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_MINUS && obj->angle > 0.2)
		obj->angle -= 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_PLUS && obj->angle < 2)
		obj->angle += 0.1;
}

static void	con_axi(t_sdl *sdl, t_cone *obj)
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
	obj->axis = *vec3f_normalize(&obj->axis);
}

static void	posi(t_sdl *sdl, t_obj *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_DOWN)
		obj->position.y -= 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_UP)
		obj->position.y += 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_RIGHT)
		obj->position.x += 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_LEFT)
		obj->position.x -= 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_KP_5)
		obj->position.z -= 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_KP_8)
		obj->position.z += 0.2;
}

void		l_cone(t_sdl *sdl, t_cone *obj, t_obj *parent)
{
	angle(sdl, obj);
	con_axi(sdl, obj);
	posi(sdl, parent);
}

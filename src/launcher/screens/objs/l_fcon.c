/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_fcyl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:48:31 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/31 15:20:06 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "l_obj.h"

static void	con_axi(t_sdl *sdl, t_fcylinder *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_4)
	{
		obj->dir.x += 0.1;
		obj->dir.x >= 1.01 && \
		obj->dir.y <= 0.002 ? obj->dir.x = -0.7 : 0;
	}
	else if (sdl->event->key.keysym.sym == SDLK_KP_6)
	{
		obj->dir.x -= 0.1;
		obj->dir.x <= -1.01 && \
		obj->dir.y <= 0.002 ? obj->dir.x = 0.7 : 0;
	}
	else if (sdl->event->key.keysym.sym == SDLK_KP_7)
	{
		obj->dir.z -= 0.1;
		obj->dir.z <= -1.01 && \
		obj->dir.y <= 0.002 ? obj->dir.z = 0.7 : 0;
	}
	else if (sdl->event->key.keysym.sym == SDLK_KP_1)
	{
		obj->dir.z += 0.1;
		obj->dir.z >= 1.01 && \
		obj->dir.y <= 0.002 ? obj->dir.z = -0.7 : 0;
	}
}

static void	posi(t_sdl *sdl, t_fcylinder *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_DOWN)
		obj->base.y -= 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_UP)
		obj->base.y += 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_RIGHT)
		obj->base.x += 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_LEFT)
		obj->base.x -= 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_KP_5)
		obj->base.z -= 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_KP_8)
		obj->base.z += 0.2;
}

void		l_fcyl(t_sdl *sdl, t_fcylinder *obj, t_obj *parent)
{
	(void)parent;
	con_axi(sdl, obj);
	posi(sdl, obj);
}

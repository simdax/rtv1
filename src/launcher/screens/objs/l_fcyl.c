/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_fcyl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:48:31 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/31 16:50:43 by alerandy         ###   ########.fr       */
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

static void	radius(t_sdl *sdl, t_fcylinder *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_PLUS && obj->radius < 5)
		obj->radius += 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_MINUS && obj->radius > 0.3)
		obj->radius -= 0.1;
}

static void	height(t_sdl *sdl, t_fcylinder *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_DIVIDE && obj->size > 0.4)
		obj->size -= 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_KP_MULTIPLY && obj->size < 5)
		obj->size += 0.2;
}

void		l_fcyl(t_sdl *sdl, t_fcylinder *obj, t_obj *parent)
{
	(void)parent;
	con_axi(sdl, obj);
	posi(sdl, obj);
	height(sdl, obj);
	radius(sdl, obj);
}

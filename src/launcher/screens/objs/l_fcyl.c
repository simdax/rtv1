/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_fcyl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:48:31 by alerandy          #+#    #+#             */
/*   Updated: 2018/06/07 16:56:21 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "l_obj.h"

static void	con_axi(t_sdl *sdl, t_fcylinder *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_4)
		obj->teta.y = (obj->teta.y + ASPEED) % 360;
	else if (sdl->event->key.keysym.sym == SDLK_KP_6)
		obj->teta.y = (obj->teta.y - ASPEED) % 360;
	else if (sdl->event->key.keysym.sym == SDLK_KP_7)
		obj->teta.x = (obj->teta.x + ASPEED) % 360;
	else if (sdl->event->key.keysym.sym == SDLK_KP_1)
		obj->teta.x = (obj->teta.x - ASPEED) % 360;
	else if (sdl->event->key.keysym.sym == SDLK_KP_9)
		obj->teta.z = (obj->teta.z + ASPEED) % 360;
	else if (sdl->event->key.keysym.sym == SDLK_KP_3)
		obj->teta.z = (obj->teta.z - ASPEED) % 360;
	obj->dir.x = 1;
	obj->dir.y = 1;
	obj->dir.z = 1;
	obj->teta.z < 0 ? obj->teta.z += 360 : 0;
	obj->teta.x < 0 ? obj->teta.x += 360 : 0;
	obj->teta.y < 0 ? obj->teta.y += 360 : 0;
	ft_rot_z(&obj->dir.x, &obj->dir.y, obj->teta.z);
	ft_rot_x(&obj->dir.y, &obj->dir.z, obj->teta.x);
	ft_rot_y(&obj->dir.x, &obj->dir.z, obj->teta.y);
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
	int		key;

	key = sdl->event->key.keysym.sym;
	(void)parent;
	if (key == SDLK_KP_4 || key == SDLK_KP_6 || key == SDLK_KP_7 || \
			key == SDLK_KP_1 || key == SDLK_KP_9 || key == SDLK_KP_3)
	con_axi(sdl, obj);
	posi(sdl, obj);
	height(sdl, obj);
	radius(sdl, obj);
}

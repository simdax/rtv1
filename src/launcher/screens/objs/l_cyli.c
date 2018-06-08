/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_cyli.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:50:24 by alerandy          #+#    #+#             */
/*   Updated: 2018/06/08 09:37:24 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "l_obj.h"

static void	radius(t_sdl *sdl, t_cylinder *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_PLUS && obj->radius < 10)
		obj->radius += 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_MINUS && obj->radius > 0.2)
		obj->radius -= 0.1;
}

static void	cyl_axi(t_sdl *sdl, t_cylinder *obj)
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
	obj->axis.x = 1;
	obj->axis.y = 1;
	obj->axis.z = 1;
	obj->teta.z < 0 ? obj->teta.z += 360 : 0;
	obj->teta.x < 0 ? obj->teta.x += 360 : 0;
	obj->teta.y < 0 ? obj->teta.y += 360 : 0;
	ft_rot_z(&obj->axis.x, &obj->axis.y, obj->teta.z);
	ft_rot_x(&obj->axis.y, &obj->axis.z, obj->teta.x);
	ft_rot_y(&obj->axis.x, &obj->axis.z, obj->teta.y);
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

void		l_cyli(t_sdl *sdl, t_cylinder *obj, t_obj *parent)
{
	int		key;

	key = sdl->event->key.keysym.sym;
	radius(sdl, obj);
	if (key == SDLK_KP_4 || key == SDLK_KP_6 || key == SDLK_KP_7 || \
			key == SDLK_KP_1 || key == SDLK_KP_9 || key == SDLK_KP_3)
		cyl_axi(sdl, obj);
	posi(sdl, parent);
}

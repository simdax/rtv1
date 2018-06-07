/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_plan.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:00:33 by alerandy          #+#    #+#             */
/*   Updated: 2018/06/07 13:35:04 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "l_obj.h"

static void	pla_axi(t_sdl *sdl, t_plane *obj)
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

static void	d_size(t_sdl *sdl, t_plane *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_PLUS)
		obj->size += 0.2;
	else if (sdl->event->key.keysym.sym == SDLK_KP_MINUS && obj->size > 0.2)
		obj->size -= 0.2;
}

void		l_plan(t_sdl *sdl, t_plane *obj, t_obj *parent)
{
	pla_axi(sdl, obj);
	posi(sdl, parent);
	if (ft_strequ(parent->tag, "disque"))
		d_size(sdl, obj);
}

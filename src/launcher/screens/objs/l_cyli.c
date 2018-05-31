/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_cyli.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:50:24 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/31 14:34:41 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "l_obj.h"

static void	radius(t_sdl *sdl, t_cylinder *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_PLUS && obj->radius2 < 100)
		obj->radius2 += 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_MINUS && obj->radius2 > 0.1)
		obj->radius2 -= 0.1;
}

static void	cyl_axi(t_sdl *sdl, t_cylinder *obj)
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

void		l_cyli(t_sdl *sdl, t_cylinder *obj, t_obj *parent)
{
	radius(sdl, obj);
	cyl_axi(sdl, obj);
	posi(sdl, parent);
}

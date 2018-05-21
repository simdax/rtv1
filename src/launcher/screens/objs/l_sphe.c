/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_sphe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:52:43 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/21 20:05:52 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "l_obj.h"

static void	radius(t_sdl *sdl, t_sphere *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_PLUS && obj->radius2 < 100)
		obj->radius2 += 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_MINUS && obj->radius2 > 0.1)
		obj->radius2 -= 0.1;
}

void		l_sphe(t_sdl *sdl, t_sphere *obj)
{
	radius(sdl, obj);
}

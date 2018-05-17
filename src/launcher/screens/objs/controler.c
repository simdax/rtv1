/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 18:14:40 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/17 18:55:34 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void	controla(t_render_opts *opts, t_sdl *sdl, t_obj *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_KP_4)
	{
		if (ft_strequ(obj->tag, "cylinder"))
		{
			obj->obj.cylinder->axis.x += 0.1;
			obj->obj.cylinder->axis.x >= 1.01 && \
	obj->obj.cylinder->axis.y <= 0.002 ? obj->obj.cylinder->axis.x = -0.7 : 0;
			obj->obj.cylinder->axis = *vec3f_normalize(&obj->obj.cylinder->axis);
		}
	}
	else if (sdl->event->key.keysym.sym == SDLK_KP_6)
	{
		if (ft_strequ(obj->tag, "cylinder"))
		{
			obj->obj.cylinder->axis.x -= 0.1;
			obj->obj.cylinder->axis.x <= -1.01 && \
	obj->obj.cylinder->axis.y <= 0.002 ? obj->obj.cylinder->axis.x = 0.7 : 0;
			obj->obj.cylinder->axis = *vec3f_normalize(&obj->obj.cylinder->axis);
		}
	}
}

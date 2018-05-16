/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_interact.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 18:51:52 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/16 19:47:28 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void	obj_key(t_render_opts *opts, t_sdl *sdl, t_obj *obj)
{
	if (sdl->event->key.keysym.sym == SDLK_DOWN)
		obj->position.y += 1;
	else if (sdl->event->key.keysym.sym == SDLK_UP)
		obj->position.y -= 1;
	else if (sdl->event->key.keysym.sym == SDLK_RIGHT)
		obj->position.x += 1;
	else if (sdl->event->key.keysym.sym == SDLK_LEFT)
		obj->position.x -= 1;
	else if (sdl->event->key.keysym.sym == 27)
		sdl->quit = 1;
	ft_printf("%s pos =\n\tx : %d\n\ty = %d\n", obj->tag, \
			(int)obj->position.x, (int)obj->position.y);
	sdl->quit == 0 ? render(opts) : 0;
	sdl->is_rendering = 0;
}

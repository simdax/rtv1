/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 18:14:40 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/19 11:24:41 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		cyl_axi(t_sdl *sdl, t_cylinder *obj)
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

void		con_axi(t_sdl *sdl, t_cone *obj)
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

void		pla_axi(t_sdl *sdl, t_plane *obj)
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

void		each_control(t_render_opts *opts, t_sdl *sdl, t_obj *obj)
{
	int		i;
	t_tfobj	**tab;

	tab = ft_memalloc(sizeof(t_tfobj *) * 5);
	tab[0] = ft_memalloc(sizeof(t_tfobj));
	tab[0]->tag = ft_strdup("cylinder");
	tab[0]->func = &cyl_axi;
	tab[1] = ft_memalloc(sizeof(t_tfobj));
	tab[1]->tag = ft_strdup("cone");
	tab[1]->func = &con_axi;
	tab[2] = ft_memalloc(sizeof(t_tfobj));
	tab[2]->tag = ft_strdup("plane");
	tab[2]->func = &pla_axi;
	i = 0;
	while (tab[i] && !ft_strequ(tab[i]->tag, obj->tag))
		i++;
	tab[i] ? tab[i]->func(sdl, obj->obj.cylinder) : 0;
	i = -1;
	while (tab[++i])
	{
		free(tab[i]->tag);
		free(tab[i]);
	}
	free(tab);
}

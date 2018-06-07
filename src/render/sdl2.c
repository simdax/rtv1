/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 16:33:25 by acourtin          #+#    #+#             */
/*   Updated: 2018/06/07 16:56:45 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "interface.h"

static void	change_scene(t_render_opts *opts)
{
	ft_printf("objects:\n");
	while (**opts->spheres)
	{
		ft_printf("%s @ %p\n", (**opts->spheres)->tag, **opts->spheres);
		++(*opts->spheres);
	}
	ft_printf("///\n");
	++(*opts->spheres);
	if (!**opts->spheres)
	{
		while (*opts->spheres != opts->orig)
			--(*opts->spheres);
	}
}

static void	key_event(t_render_opts *opts, t_sdl *sdl)
{
	if (sdl->event->key.keysym.sym == SDLK_DOWN)
		opts->camorig.z += 1;
	else if (sdl->event->key.keysym.sym == SDLK_UP)
		opts->camorig.z -= 1;
	else if (sdl->event->key.keysym.sym == SDLK_RIGHT)
		opts->camorig.x += 1;
	else if (sdl->event->key.keysym.sym == SDLK_LEFT)
		opts->camorig.x -= 1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_8)
		opts->camdir.y += 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_5)
		opts->camdir.y -= 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_6)
		opts->camdir.x += 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_KP_4)
		opts->camdir.x -= 0.1;
	else if (sdl->event->key.keysym.sym == SDLK_a)
		change_scene(opts);
	else if (sdl->event->key.keysym.sym == SDLK_s)
		snap_screen(opts, sdl);
	vec3f_normalize(&(opts->camdir));
	sdl->event->key.keysym.sym == 27 ? sdl->quit = 1 : 0;
	while ((sdl->event->key.keysym.sym == 27 || sdl->event->key.keysym.sym == \
				SDLK_a || sdl->event->key.keysym.sym == SDLK_s) \
				&& sdl->event->type == SDL_KEYDOWN)
		;
}

void		check_event(t_render_opts *opts, t_sdl *sdl, t_thrprm *prm)
{
	if (sdl->event->key.keysym.sym != SDLK_s)
		opts->it = ITRES;
	if (prm->sobj)
		obj_key(opts, sdl, prm->sobj);
	else
		key_event(opts, sdl);
}

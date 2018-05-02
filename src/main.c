/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:55:18 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/02 18:13:38 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "object.h"
#include "parser.h"
#include "mini_ls.h"

void	draw(int *pixel, int index, t_vec3f *colors)
{
	int	color;

	color = 0;
	color = (int)(colors->z / (colors->z + 1) * 255);
	color += (int)(colors->y / (colors->y + 1) * 255) << 8;
	color += (int)(colors->x / (colors->x + 1) * 255) << 16;
	pixel[index] = color;
}

void	through_argv(t_thrprm *param)
{
	int				*screen;
	t_config		config;
	t_conf			*conf;
	t_render_opts	opts;

	conf = read_configuration(param->scn, "configs/rules");
	screen = malloc(sizeof(int) * conf->globals.width * conf->globals.height);
	config = (t_config){1 / (float)conf->globals.width, 1 /
						(float)conf->globals.height,
						70, conf->globals.width /
						(float)conf->globals.height, 0};
	config.angle = tan(M_PI * 0.5 * config.fov / 180.0);
	opts = (t_render_opts){
		conf->objects, screen, &config,
		conf->globals.from, conf->globals.to,
		conf->globals.width, conf->globals.height,
		matrix_new(conf->globals.from, conf->globals.to, (t_vec3f){0, 1, 0})
	};
	render(&opts);
	init_sdl(&opts, param->event);
	free(screen);
}

int		main(void)
{
	ft_printf("Coucou 🤡\n");
	mini_ls();
	ft_printf("Au revoir ❤️\n");
	return (0);
}

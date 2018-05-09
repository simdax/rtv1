/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:55:18 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/09 13:48:57 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "object.h"
#include "parser.h"

void	draw(int *pixel, int index, t_vec3f *colors)
{
	int	color;

	color = 0;
	color = (int)(colors->z / (colors->z + 1) * 255);
	color += (int)(colors->y / (colors->y + 1) * 255) << 8;
	color += (int)(colors->x / (colors->x + 1) * 255) << 16;
	pixel[index] = color;
}

void	through_argv(char *argv)
{
	int				*screen;
	t_config		config;
	t_conf			*conf;
	t_render_opts	opts;

	if (!(conf = read_configuration(argv, "configs/rules")))
		return ;
	screen = malloc(sizeof(int) * conf->globals.width * conf->globals.height);
	config = (t_config){1 / (double)conf->globals.width, 1 /
						(double)conf->globals.height,
						70, conf->globals.width /
						(double)conf->globals.height, 0};
	config.angle = tan(M_PI * 0.5 * config.fov / 180.0);
	opts = (t_render_opts){
		&conf->objects, screen, &config,
		conf->globals.from, conf->globals.to,
		conf->globals.width, conf->globals.height,
		matrix_new(conf->globals.from, conf->globals.to, (t_vec3f){0, 1, 0})
	};
	render(&opts);
	init_sdl(&opts);
	free(screen);
	ft_lstdel(&conf->tmp_objects, object_del);
}

int		main(int argc, char **argv)
{
	ft_printf("coucou 🤡");
	if (argc != 2)
		return (0);
	else
		through_argv(argv[1]);
	ft_printf("au revoir ❤️");
	return (0);
}

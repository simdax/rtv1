/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 16:33:41 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/10 21:01:58 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "object.h"

void	draw(int *pixel, int index, t_vec3f *colors)
{
	int	color;

	color = 0;
	color = (int)(fmin(1.0, colors->z) * 255);
	color += (int)(fmin(1.0, colors->y) * 255) << 8;
	color += (int)(fmin(1.0, colors->x) * 255) << 16;
	pixel[index] = color;
}

void	free_objs(t_obj ***objects)
{
	t_obj	**objs;

	objs = *objects;
	while (*objs)
		free(*objs++);
	free(*objects);
}

void	through_argv(char *argv)
{
	t_obj			**objects;
	int				*screen;
	t_config		config;
	t_render_opts	opts;

	config = (t_config){1 / (float)WIDTH, 1 / (float)HEIGHT,
						70, WIDTH / (float)HEIGHT, 0};
	config.angle = tan(M_PI * 0.5 * config.fov / 180.0);
	objects = read_configuration(argv, "configs/rules")->objects;
	screen = malloc(sizeof(int) * WIDTH * HEIGHT);
	opts = (t_render_opts){
		objects, screen, &config, (t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0}
	};
	render(&opts);
	init_sdl(&opts);
	free(screen);
	free_objs(&objects);
}

int		main(int argc, char **argv)
{

	if (argc != 2)
		return (0);
	else
		through_argv(argv[1]);
	return (0);
}

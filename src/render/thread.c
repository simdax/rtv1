/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 18:20:01 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/16 18:20:01 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec3f	create_ray(unsigned x, unsigned y,
						t_render_opts *opts)
{
	t_vec3f	result;

	result = ((t_vec3f){
			(2 * ((x + 0.5) * opts->config->inv_width) - 1) *
				opts->config->angle *
				opts->config->aspectratio,
				(1 - 2 * ((y + 0.5) *
				opts->config->inv_height)) * opts->config->angle,
				-1});
	vec3f_normalize(&result);
	return (result);
}

void			*render_f(void *render_opts)
{
	t_vec3f			color;
	unsigned		y;
	unsigned		x;
	t_render_opts	*opts;
	t_vec3f			raydir;

	opts = ((t_thread*)render_opts)->opts;
	opts->matrix = matrix_new(opts->camorig, opts->camdir, (t_vec3f){0, 1, 0});
	y = ((t_thread*)render_opts)->from;
	while (y < ((t_thread*)render_opts)->to)
	{
		x = 0;
		while (x < opts->width)
		{
			raydir = create_ray(x, y, opts);
			vec3f_normalize(&raydir);
			raydir = matrix_mul(opts->matrix, raydir);
			trace(&((t_ray){INFINITY, opts->camorig, raydir, -1}),
				opts->spheres, 0, &color);
			draw(opts->pixels, (y * opts->width) + x, &color);
			++x;
		}
		++y;
	}
	pthread_exit(0);
}

int				render(t_render_opts *opts)
{
	pthread_t		*threads;
	t_thread		*args;
	int				i;
	int				u;

	if (!(threads = malloc(sizeof(pthread_t) * 8)))
		return (0);
	if (!(args = malloc(sizeof(t_thread) * 8)))
		return (0);
	i = 0;
	while (i < 8)
	{
		args[i] = (t_thread){(opts->height * i) / 8, (opts->height * (i + 1)) /
								8, i, opts};
		u = pthread_create(&threads[i], NULL, render_f, &(args[i]));
		++i;
	}
	i = 0;
	while (i < 8)
		pthread_join(threads[i++], NULL);
	free(threads);
	free(args);
	return (1);
}
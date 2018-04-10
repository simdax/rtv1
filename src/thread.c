/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 16:46:46 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/10 17:58:51 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_33mat	matrix_new(t_vec3f to, t_vec3f from, t_vec3f tmp)
{
    t_33mat	matrix;

    matrix.forward = from;
    vec3f_sub2(&matrix.forward, &to);
    vec3f_normalize(&matrix.forward);
    matrix.right = vec3f_cross(&tmp, &matrix.forward);
    matrix.up = vec3f_cross(&matrix.forward, &matrix.right);
    return (matrix);
}

static t_vec3f	create_ray(unsigned x, unsigned y,
                           t_render_opts *opts)
{
    t_vec3f	result;

    result = ((t_vec3f){
            (2 * ((x + 0.5) * opts->config->invWidth) - 1) *
                opts->config->angle *
                opts->config->aspectratio,
                (1 - 2 * ((y + 0.5) *
                          opts->config->invHeight)) * opts->config->angle,
                -1
                });
    vec3f_normalize(&result);
    return (result);
}

void			*render_f(void *render_opts)
{
    t_vec3f			color;
    unsigned		y;
    unsigned		x;
    t_render_opts	*opts;
    t_33mat		matrix;
    
    opts = ((t_thread*)render_opts)->opts;
    y = ((t_thread*)render_opts)->from;
    matrix = matrix_new(opts->camorig, opts->camdir, (t_vec3f){0, 1, 0});
    while (y < ((t_thread*)render_opts)->to)
    {
        x = 0;
        while (x < WIDTH)
        {
            trace(&((t_ray){INFINITY, opts->camorig,
                            matrix_mul(matrix, create_ray(x, y, opts)),
                            -1}),
                  opts->spheres, 0, &color);
            draw(opts->pixels, (y * WIDTH) + x, &color);
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
        args[i] = (t_thread){(HEIGHT * i) / 8, (HEIGHT * (i + 1)) / 8, i, opts};
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

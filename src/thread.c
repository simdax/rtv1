/* ************************************************************************** */
/*																																						*/
/*																												:::			 ::::::::		*/
/*	 thread.c																						:+:			 :+:		:+:		*/
/*																										+:+ +:+					+:+			*/
/*	 By: scornaz <marvin@42.fr>											+#+	 +:+			 +#+				*/
/*																								+#+#+#+#+#+		+#+						*/
/*	 Created: 2018/04/03 16:46:46 by scornaz					 #+#		#+#							*/
/*   Updated: 2018/04/10 16:00:05 by scornaz          ###   ########.fr       */
/*																																						*/
/* ************************************************************************** */

#include "rtv1.h"

t_camera		s_cam(t_vec3f lkfrom, t_vec3f lkat, t_vec3f vup, double fov)
{
		t_vec3f			v[3];
		t_vec3f			temp[2];
		t_camera		cam;
		double			half_height;
		double			half_width;

		cam.origin = v_set(lkfrom.x, lkfrom.y, lkfrom.z);
		fov = fov * M_PI / 180;
		half_height = tan(fov / 2);
		half_width = ((double)W_LENGHT / (double)W_WIDTH) * half_height;
		v[2] = v_normalize(v_less(lkfrom, lkat));
		v[1] = v_normalize(v_cross(vup, v[2]));
		v[0] = v_cross(v[2], v[1]);
		cam.lowleftcor = v_set(-half_width, -half_height, -1.0);
		temp[0] = v_mult(v[1], half_width);
		temp[1] = v_mult(v[0], half_height);
		cam.lowleftcor = v_less(v_less(v_less(cam.origin, temp[0]), temp[1]), v[2]);
		cam.horizontal = v_mult(v[1], 2 * half_width);
		cam.vertical = v_mult(v[0], 2 * half_height);
		return (cam);
}

static t_vec3f	create_ray(unsigned x, unsigned y,
						t_render_opts *opts)
{
	return ((t_vec3f){
			(2 * ((x + 0.5) * opts->config->invWidth) - 1) *
				opts->config->angle *
				opts->config->aspectratio,
				(1 - 2 * ((y + 0.5) *
						opts->config->invHeight)) * opts->config->angle,
				-1
				});
}

void			*render_f(void *render_opts)
{
	t_vec3f			raydir;
	t_vec3f			color;
	unsigned		y;
	unsigned		x;
	t_render_opts	*opts;

	opts = ((t_thread*)render_opts)->opts;
	y = ((t_thread*)render_opts)->from;
	while (y < ((t_thread*)render_opts)->to)
	{
		x = 0;
		while (x < WIDTH)
		{
			raydir = create_ray(x, y, opts);
			vec3f_normalize(&raydir);
			trace(&((t_ray){INFINITY, opts->camorig, raydir, -1}),
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

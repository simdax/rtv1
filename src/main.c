/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:55:18 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/18 16:15:52 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "object.h"
#include "parser.h"
#include "mini_ls.h"

void		draw(int *pixel, int index, t_vec3f *colors)
{
	int	color;

	color = 0;
	if (SMOOTH_LIGHT)
	{
		color = (int)(colors->z / (colors->z + 1) * 255);
		color += (int)(colors->y / (colors->y + 1) * 255) << 8;
		color += (int)(colors->x / (colors->x + 1) * 255) << 16;
	}
	else
	{
		color = (int)(fmin(1.0, colors->z) * 255);
		color += (int)(fmin(1.0, colors->y) * 255) << 8;
		color += (int)(fmin(1.0, colors->x) * 255) << 16;
	}
	pixel[index] = color;
}

static void	set(t_config *config, t_conf *conf, t_render_opts *opts, \
		int *screen)
{
	int		*rended;

	rended = ft_memalloc(sizeof(int) * conf->globals.width \
			* conf->globals.height);
	*config = (t_config){1 / (double)conf->globals.width, 1 /
						(double)conf->globals.height,
						70, conf->globals.width /
						(double)conf->globals.height, 0};
	(*config).angle = tan(M_PI * 0.5 * (*config).fov / 180.0);
	*opts = (t_render_opts){
		&conf->objects, screen, rended, &(*config),
		conf->globals.from, conf->globals.to,
		conf->globals.width, conf->globals.height,
		matrix_new(conf->globals.from, conf->globals.to, (t_vec3f){0, 1, 0}),
		conf->objects, 1};
}

void		through_argv(t_thrprm *param)
{
	int				*screen;
	t_config		config;
	t_conf			*conf;
	t_render_opts	opts;
	t_obj			**tmp_obj;

	!(conf = read_configuration(param->scn, "configs/rules")) ? \
			(param->quited = 1) : 0;
	param->width > 100 ? conf->globals.width = param->width : 0;
	param->height > 100 ? conf->globals.height = param->height : 0;
	!param->quited && !(screen = malloc(sizeof(int) * conf->globals.width * \
					conf->globals.height)) ? (param->quited = 1) : 0;
	if (param->quited)
		return ;
	set(&config, conf, &opts, screen);
	tmp_obj = conf->objects;
	render(&opts);
	init_sdl(&opts, param);
	param->sobj = 0;
	param->sdl = NULL;
	free(screen);
	free(opts.rended);
	ft_lstdel(&conf->tmp_objects, object_del);
	free(tmp_obj);
	free(conf);
}

int			main(void)
{
	ft_printf("Coucou 🤡\n");
	mini_ls();
	ft_printf("Au revoir ❤️\n");
	return (0);
}

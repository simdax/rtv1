/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:55:18 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/25 16:10:26 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "object.h"
#include "parser.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#define _DIRENT struct dirent

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

	conf = read_configuration(argv, "configs/rules");
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
	init_sdl(&opts);
	free(screen);
}

void	choose_scn(char **scn, int nbr)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	ft_printf("Veuillez choisir une scêne parmi celles ci-dessous :\n");
	while (i < nbr)
	{
		ft_printf("%d - %s\n", i, scn[i] + 7);
		i++;
	}
	ft_printf("(Tapez leur ID de 0 à %d) : ", nbr - 1);
	get_next_line(0, &line);
	while ((i = ft_atoi(line)) < 0 || i > nbr)
	{
		ft_printf("J'ai dit, de 0 à %d : ", nbr - 1);
		get_next_line(0, &line);
	}
	through_argv(scn[i]);
}

int		count_file(void)
{
	_DIRENT	*fold;
	int		i;
	DIR		*dir;

	dir = NULL;
	fold = NULL;
	i = 0;
	if (!(dir = opendir("scenes")))
	{
		ft_putendl("Une erreur est survenue lors de l'ouverture des scènes.");
		exit(0);
	}
	else
	{
		while ((fold = readdir(dir)))
			if (fold->d_name[0] != '.')
				i++;
	}
	return (i);
}

void	mini_ls(void)
{
	int		i;
	DIR		*dir;
	_DIRENT	*fold;
	char	**scn;
	int		file;

	dir = NULL;
	fold = NULL;
	scn = NULL;
	i = 0;
	file = count_file();
	if (!(dir = opendir("scenes")))
		ft_putendl("Une erreur est survenue lors de l'ouverture des scènes.");
	else
	{
		if ((scn = ft_memalloc(sizeof(char*) * file)))
		{
			while ((fold = readdir(dir)))
				if (fold->d_name[0] != '.')
					scn[i++] = ft_strjoin("scenes/", fold->d_name);
			choose_scn(scn, file);
		}
	}
}

int		main(int argc, char **argv)
{
	ft_printf("Coucou 🤡\n");
	if (argc != 2)
		mini_ls();
	else
		through_argv(argv[1]);
	ft_printf("Au revoir ❤️\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 16:19:45 by alerandy          #+#    #+#             */
/*   Updated: 2018/04/26 13:41:14 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_ls.h"

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
	while ((i = ft_atoi(line)) < 0 || i > nbr || !line[0])
	{
		ft_strdel(&line);
		ft_printf("J'ai dit, de 0 à %d : ", nbr - 1);
		get_next_line(0, &line);
	}
	ft_strdel(&line);
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
		{
			if (fold->d_name[0] != '.')
				i++;
		}
	}
	closedir(dir);
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
			closedir(dir);
			choose_scn(scn, file);
		}
	}
}

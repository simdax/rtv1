/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:18:32 by cbesse            #+#    #+#             */
/*   Updated: 2018/04/10 18:03:10 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	attr_sphere(t_sphere *sphere, char **tab)
{
	tab[3][ft_strlen(tab[3]) - 1] = '\0';
	sphere->center.x = ft_atof(tab[1] + 1);
	sphere->center.y = ft_atof(tab[2]);
	sphere->center.z = ft_atof(tab[3]);
	sphere->radius = ft_atof(tab[4]);
}

void	attr_plan(t_plan *plan, char **tab)
{
	tab[3][ft_strlen(tab[3]) - 1] = '\0';
	tab[6][ft_strlen(tab[6]) - 1] = '\0';
	plan->point.x = ft_atof(tab[1] + 1);
	plan->point.y = ft_atof(tab[2]);
	plan->point.z = ft_atof(tab[3]);
	plan->vdir.x = ft_atof(tab[4] + 1);
	plan->vdir.y = ft_atof(tab[5]);
	plan->vdir.z = ft_atof(tab[6]);
	plan->vdir = v_normalize(plan->vdir);
	plan->size = 0;
}

int		set_sphere(t_scene *scene, char **tab)
{
	int	j;

	j = 0;
	while (tab[j++])
		;
	if (j - 1 != 10)
		return (-1);
	scene->list[scene->i].form = (t_sphere *)ft_memalloc(1 * sizeof(t_sphere));
	attr_sphere(scene->list[scene->i].form, tab);
	scene->list[scene->i].color.x = ft_atof(tab[5] + 1);
	scene->list[scene->i].color.y = ft_atof(tab[6]);
	tab[7][ft_strlen(tab[7]) - 1] = '\0';
	scene->list[scene->i].color.z = ft_atof(tab[7]);
	scene->list[scene->i].ks = ft_atof(tab[8]);
	scene->list[scene->i].kt = ft_atof(tab[9]);
	scene->list[scene->i].type = 1;
	scene->i++;
	j = 0;
	while (j < scene->i)
		scene->list[j++].size = scene->i;
	return (1);
}

int		set_plan(t_scene *scene, char **tab)
{
	int	j;

	j = 0;
	while (tab[j++])
		;
	if (j - 1 != 12)
		return (-1);
	scene->list[scene->i].form = (t_plan *)ft_memalloc(1 * sizeof(t_plan));
	attr_plan(scene->list[scene->i].form, tab);
	scene->list[scene->i].color.x = ft_atof(tab[7] + 1);
	scene->list[scene->i].color.y = ft_atof(tab[8]);
	tab[9][ft_strlen(tab[9]) - 1] = '\0';
	scene->list[scene->i].color.z = ft_atof(tab[9]);
	scene->list[scene->i].ks = ft_atof(tab[10]);
	scene->list[scene->i].kt = ft_atof(tab[11]);
	scene->list[scene->i].type = 2;
	scene->i++;
	j = 0;
	while (j < scene->i)
		scene->list[j++].size = scene->i;
	return (1);
}

int		set_light(t_scene *scene, char **tab)
{
	int j;

	j = 0;
	while (tab[j++])
		;
	if (j - 1 != 4)
		return (-1);
	tab[3][ft_strlen(tab[3]) - 1] = '\0';
	scene->light[scene->k].x = ft_atof(tab[1] + 1);
	scene->light[scene->k].y = ft_atof(tab[2]);
	scene->light[scene->k].z = ft_atof(tab[3]);
	scene->k++;
	return (1);
}

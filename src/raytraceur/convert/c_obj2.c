/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_obj2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 10:43:19 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/30 10:52:35 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rtv1.h"

static void	sphere_def2(t_sphere *sphere, t_sphere2 *sphere2, t_obj *obj)
{
	sphere2->center.x = obj->position.x;
	sphere2->center.y = obj->position.y;
	sphere2->center.z = obj->position.z;
	sphere2->radius = sphere->radius;
}

void		sphere_def(t_obj *obj, t_scene *scene)
{
	int j;

	j = 0;
	scene->list[scene->i].form =
		(t_sphere2 *)ft_memalloc(1 * sizeof(t_sphere2));
	sphere_def2(obj->obj.sphere, scene->list[scene->i].form, obj);
	scene->list[scene->i].color.x = obj->surface_color.x;
	scene->list[scene->i].color.y = obj->surface_color.y;
	scene->list[scene->i].color.z = obj->surface_color.z;
	scene->list[scene->i].ks = obj->reflection;
	scene->list[scene->i].kt = obj->transparency;
	scene->list[scene->i].type = 1;
	scene->list[scene->i].index = scene->i;
	scene->i++;
	while (j < scene->i)
		scene->list[j++].size = scene->i;
}

static void	plan_def2(t_plane *pl, t_plan *plan, t_obj *obj)
{
	plan->point.x = obj->position.x;
	plan->point.y = obj->position.y;
	plan->point.z = obj->position.z;
	plan->vdir.x = pl->axis.x;
	plan->vdir.y = pl->axis.y;
	plan->vdir.z = pl->axis.z;
	plan->vdir = v_normalize(plan->vdir);
	plan->size = 0;
}

void		plan_def(t_obj *obj, t_scene *scene)
{
	int j;

	j = 0;
	scene->list[scene->i].form = (t_plan *)ft_memalloc(sizeof(t_plan));
	plan_def2(obj->obj.plane, scene->list[scene->i].form, obj);
	scene->list[scene->i].color.x = obj->surface_color.x;
	scene->list[scene->i].color.y = obj->surface_color.y;
	scene->list[scene->i].color.z = obj->surface_color.z;
	scene->list[scene->i].ks = obj->reflection;
	scene->list[scene->i].kt = obj->transparency;
	scene->list[scene->i].type = 2;
	scene->list[scene->i].index = scene->i;
	scene->i++;
	while (j < scene->i)
		scene->list[j++].size = scene->i;
}

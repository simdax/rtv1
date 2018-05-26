/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 00:37:36 by cbesse            #+#    #+#             */
/*   Updated: 2018/05/26 17:21:29 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rtv1.h"

void	sphere_def2(t_sphere *sphere, t_sphere2 *sphere2, t_obj *obj)
{
	sphere2->center.x = obj->position.x;
	sphere2->center.y = obj->position.y;
	sphere2->center.z = obj->position.z;
	sphere2->radius = sphere->radius;
}

void	sphere_def(t_obj *obj, t_scene *scene)
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

void	plan_def2(t_plane *pl, t_plan *plan, t_obj *obj)
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

void	plan_def(t_obj *obj, t_scene *scene)
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

void	cylindre_def2(t_cylinder *cyl, t_cylindre *cylindre, t_obj *obj)
{
	cylindre->base.x = obj->position.x;
	cylindre->base.y = obj->position.y;
	cylindre->base.z = obj->position.z;
	cylindre->radius = cyl->radius;
	cylindre->dir.x = cyl->axis.x;
	cylindre->dir.y = cyl->axis.y;
	cylindre->dir.z = cyl->axis.z;
	cylindre->dir = v_normalize(cylindre->dir);
}

void	cylindre_def(t_obj *obj, t_scene *scene)
{
	int j;

	j = 0;
	scene->list[scene->i].form =
		(t_cylindre *)ft_memalloc(1 * sizeof(t_cylindre));
	cylindre_def2(obj->obj.cylinder, scene->list[scene->i].form, obj);
	scene->list[scene->i].color.x = obj->surface_color.x;
	scene->list[scene->i].color.y = obj->surface_color.y;
	scene->list[scene->i].color.z = obj->surface_color.z;
	scene->list[scene->i].ks = obj->reflection;
	scene->list[scene->i].kt = obj->transparency;
	scene->list[scene->i].type = 3;
	scene->list[scene->i].index = scene->i;
	scene->i++;
	while (j < scene->i)
		scene->list[j++].size = scene->i;
}

void	cone_def2(t_cone *co, t_cone2 *cone, t_obj *obj)
{
	cone->apex.x = obj->position.x;
	cone->apex.y = obj->position.y;
	cone->apex.z = obj->position.z;
	cone->angle = co->angle;
	cone->dir.x = co->axis.x;
	cone->dir.y = co->axis.y;
	cone->dir.z = co->axis.z;
	cone->dir = v_normalize(cone->dir);
}

void	cone_def(t_obj *obj, t_scene *scene)
{
	int j;

	j = 0;
	scene->list[scene->i].form = (t_cone2 *)ft_memalloc(sizeof(t_cone2));
	cone_def2(obj->obj.cone, scene->list[scene->i].form, obj);
	scene->list[scene->i].color.x = obj->surface_color.x;
	scene->list[scene->i].color.y = obj->surface_color.y;
	scene->list[scene->i].color.z = obj->surface_color.z;
	scene->list[scene->i].ks = obj->reflection;
	scene->list[scene->i].kt = obj->transparency;
	scene->list[scene->i].type = 4;
	scene->list[scene->i].index = scene->i;
	scene->i++;
	while (j < scene->i)
		scene->list[j++].size = scene->i;
}

void	light_def(t_sphere *sphere, t_scene *scene)
{
	int j;

	j = 0;
	scene->light[scene->k].x = sphere->center.x;
	scene->light[scene->k].y = sphere->center.y;
	scene->light[scene->k].z = sphere->center.z;
	scene->k++;
}

void	count_obj(t_obj **obj, t_scene *scene)
{
	int k;

	k = 0;
	while (obj[k])
	{
		if (ft_strequ(obj[k]->tag, "sphere"))
			scene->n_obj++;
		else if (ft_strequ(obj[k]->tag, "light"))
			scene->n_light++;
		else if (ft_strequ(obj[k]->tag, "cone"))
			scene->n_obj++;
		else if (ft_strequ(obj[k]->tag, "plane"))
			scene->n_obj++;
		else if (ft_strequ(obj[k]->tag, "cylinder"))
			scene->n_obj++;
		else if (ft_strequ(obj[k]->tag, "fcylinder"))
			scene->n_obj++;
		else if (ft_strequ(obj[k]->tag, "fcone"))
			scene->n_obj++;
		k++;
	}
}

void	ft_convert2(t_obj **obj, t_scene *scene, int i)
{
	if (ft_strequ(obj[i]->tag, "plane"))
		plan_def(obj[i], scene);
	if (ft_strequ(obj[i]->tag, "cylinder"))
		cylindre_def(obj[i], scene);
	if (ft_strequ(obj[i]->tag, "fcylinder"))
		fcylindre_def(obj[i], scene);
	if (ft_strequ(obj[i]->tag, "fcone"))
		def_fcone(obj[i], scene);
}

void	ft_convert(t_obj **obj, t_scene *scene)
{
	int i;

	i = 0;
	scene->n_light = 0;
	scene->n_obj = 0;
	count_obj(obj, scene);
	scene->list = (t_formlist *)ft_memalloc(scene->n_obj * sizeof(t_formlist));
	scene->light = (t_vecteur *)ft_memalloc(scene->n_light * sizeof(t_vecteur));
	scene->i = 0;
	scene->k = 0;
	while (obj[i])
	{
		if (ft_strequ(obj[i]->tag, "sphere"))
			sphere_def(obj[i], scene);
		else if (ft_strequ(obj[i]->tag, "light"))
			light_def(obj[i]->obj.sphere, scene);
		else if (ft_strequ(obj[i]->tag, "cone"))
			cone_def(obj[i], scene);
		else if (ft_strequ(obj[i]->tag, "plane"))
			plan_def(obj[i], scene);
		else if (ft_strequ(obj[i]->tag, "cylinder"))
			cylindre_def(obj[i], scene);
		else if (ft_strequ(obj[i]->tag, "fcylinder"))
			fcylindre_def(obj[i], scene);
		else if (ft_strequ(obj[i]->tag, "fcone"))
			def_fcone(obj[i], scene);
		i++;
	}
}

void	ft_raytrace(t_scene *scene, t_vec3f *color, t_vec3f ori, t_vec3f dir)
{
	t_vecteur	vr;
	t_ray2		ray;

	ray.ori = v_set(ori.x, ori.y, ori.z);
	ray.dir = v_set(dir.x, dir.y, dir.z);
	vr = r_color(&ray, *scene, 0);
	color->x = vr.x;
	color->y = vr.y;
	color->z = vr.z;
}

t_obj	*ft_objtouche(t_obj **lst, t_ray *tmp)
{
	t_scene		*scene;
	t_ray2		ray;
	t_record	rec;
	double		*min_max;
	int			i;

	i = -1;
	min_max = (double *)ft_memalloc(2 * sizeof(double));
	set_min_max(0.0, DBL_MAX, min_max);
	ray.ori = v_set(tmp->rayorig.x, tmp->rayorig.y, tmp->rayorig.z);
	ray.dir = v_set(tmp->raydir.x, tmp->raydir.y, tmp->raydir.z);
	scene = ft_memalloc(sizeof(t_scene));
	ft_convert(lst, scene);
	if (hit_qqch(scene->list, &ray, min_max, &rec))
	{
		while ((ft_strequ(lst[++i]->tag, "light")))
			rec.index++;
		while (i < rec.index)
			if (ft_strequ(lst[i++]->tag, "light"))
				rec.index++;
	}
	free_scene(scene);
	free(min_max);
	return (lst[i]);
}

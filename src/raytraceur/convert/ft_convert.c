/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 10:40:29 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/30 10:50:05 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rtv1.h"

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

	i = -1;
	scene->n_light = 0;
	scene->n_obj = 0;
	count_obj(obj, scene);
	scene->list = (t_formlist *)ft_memalloc(scene->n_obj * sizeof(t_formlist));
	scene->light = (t_vecteur *)ft_memalloc(scene->n_light * sizeof(t_vecteur));
	scene->i = 0;
	scene->k = 0;
	while (obj[++i])
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

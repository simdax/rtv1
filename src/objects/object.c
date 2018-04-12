/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:35:14 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/12 17:35:19 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_obj	object_new(char *type, char *parent)
{
	t_obj	new;

	new.tag = type;
	new.reflection = 0;
	new.transparency = 0;
	new.emission_color = (t_vec3f){0, 0, 0};
	new.surface_color = (t_vec3f){0, 0, 0};
	if (ft_strequ(type, "light") || ft_strequ(type, "sphere"))
		new.obj.sphere = sphere_new((t_vec3f){0, 0, 0}, 0);
	if (ft_strequ(type, "cone"))
		new.obj.cone =
			cone_new(0, INFINITY, (t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0});
	if (ft_strequ(type, "plane"))
		new.obj.sphere = sphere_new((t_vec3f){0, 0, 0}, 0);
	if (ft_strequ(type, "cylinder"))
		new.obj.cylinder =
			cylinder_new((t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0}, 1);
	return (new);
}

void	object_del(void *el, size_t size)
{
	t_obj	*obj;

	obj = el;
	ft_memdel((void**)&obj->obj);
//	ft_memdel(&obj->tag);
}

void	object_normale(t_obj *obj, t_ray *hit)
{
	t_vec3f	tmp;

	vec3f_cpy(&tmp, &hit->raydir);
	vec3f_mul_unit2(&tmp, hit->tnear);
	vec3f_cpy(&hit->phit, &hit->rayorig);
	vec3f_add2(&hit->phit, &tmp);
	vec3f_cpy(&hit->nhit, &hit->phit);
	if (ft_strequ(obj->tag, "sphere"))
		sphere_normale(obj->obj.sphere, hit);
	else if (ft_strequ(obj->tag, "light"))
		sphere_normale(obj->obj.sphere, hit);
	else if (ft_strequ(obj->tag, "cone"))
		cone_normale(obj->obj.cone, hit);
	else if (ft_strequ(obj->tag, "plane"))
		plane_normale(obj->obj.plane, hit);
	else if (ft_strequ(obj->tag, "cylinder"))
		cylinder_normale(obj->obj.cylinder, hit);
	else
		printf("pas de normale");
	vec3f_normalize(&hit->nhit);
	if (vec3f_dot(&hit->raydir, &hit->nhit) > 0)
	{
		vec3f_negate(&hit->nhit);
		hit->inside = 1;
	}
}

int		object_intersect(t_obj *obj, t_ray *hit, float *t0)
{
	vec3f_cpy(&hit->distance, &hit->rayorig);
	vec3f_sub2(&hit->distance, &obj->position);
	if (ft_strequ(obj->tag, "sphere"))
		return (sphere_intersect(obj->obj.sphere, hit, t0));
	else if (ft_strequ(obj->tag, "light"))
		return (sphere_intersect(obj->obj.sphere, hit, t0));
	else if (ft_strequ(obj->tag, "cone"))
		return (cone_intersect(obj->obj.cone, hit, t0));
	else if (ft_strequ(obj->tag, "plane"))
		return (plane_intersect(obj->obj.plane, hit, t0));
	else if (ft_strequ(obj->tag, "cylinder"))
		return (cylinder_intersect(obj->obj.cylinder, hit, t0));
	else
	{
		printf("pas d'intersection");
		return (0);
	}
}

void	object_print(t_obj *obj)
{
	printf("type : %s @ %p\n", obj->tag, obj);
	printf("transparency: %g\nreflection : %g\n", obj->transparency,
		obj->reflection);
	printf("emissionColor : ");
	vec3f_print(&(obj->emission_color));
	printf("surfaceColor : ");
	vec3f_print(&(obj->surface_color));
	printf("position : ");
	vec3f_print(&(obj->position));
	if (ft_strequ(obj->tag, "sphere"))
		sphere_print(obj->obj.sphere);
	if (ft_strequ(obj->tag, "cone"))
		cone_print(obj->obj.cone);
	if (ft_strequ(obj->tag, "cylinder"))
		cylinder_print(obj->obj.cylinder);
	if (ft_strequ(obj->tag, "plane"))
		plane_print(obj->obj.plane);
	if (ft_strequ(obj->tag, "light"))
		sphere_print(obj->obj.sphere);
	printf("\\\\\\\\\\\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:35:14 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/02 14:50:24 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_obj object_new(char *type, char *parent)
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
		new.obj.cone = cone_new(0, INFINITY, (t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0});
	if (ft_strequ(type, "plane"))
		new.obj.sphere = sphere_new((t_vec3f){0, 0, 0}, 0);
	if (ft_strequ(type, "cylinder"))
		new.obj.cylinder = cylinder_new((t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0}, 1);
	return (new);
}

void	del_object(void *c, size_t size)
{
	t_obj		*content;

	/* content = c; */
	/* if (content) */
	/*   { */
	/*     free(content->tag); */
	/*     content->tag = 0; */
	/*     //free(content->obj.sphere); */
	/*   } */
	/* free(content); */
	/* content = 0; */
}

void	square_set(t_obj *obj, char *prop, char *type, float *val)
{
	if (ft_strequ(type, "sphere"))
    {
		obj->obj.sphere->radius = *val;
		obj->obj.sphere->radius2 = *val * *val;
    }
	else if (ft_strequ(type, "cylinder"))
    {
		obj->obj.cylinder->radius = *val;
		obj->obj.cylinder->radius2 = *val * *val;
    }
	else if (ft_strequ(prop, "angle"))
    {
		obj->obj.cone->angle = *val;
		obj->obj.cone->angle2 = *val * *val;
		obj->obj.cone->tan_angle = tan(*val / 2);
		obj->obj.cone->tan_angle2 = 1 + tan(*val / 2) * tan(*val / 2);
    }
}

void	object_set(t_obj *obj, char *prop, char *type, void *val)
{
	if (ft_strequ(prop, "position"))
    {
		obj->position = *((t_vec3f*)val);
		if (ft_strequ(type, "plane"))
		{
			vec3f_set(&(obj->obj.plane->position),
					  ((float*)val)[0],
					  ((float*)val)[1],
					  ((float*)val)[2]);
		}
		if (ft_strequ(type, "cone"))
		{
			vec3f_set(&(obj->obj.cone->tip_position),
					  ((float*)val)[0],
					  ((float*)val)[1],
					  ((float*)val)[2]);
		}
		else if (ft_strequ(type, "plane"))
		{
			vec3f_set(&(obj->obj.sphere->center),
					  ((float*)val)[0],
					  ((float*)val)[1],
					  ((float*)val)[2]);
		}
		else
		{
			vec3f_set(&(obj->obj.sphere->center),
					  ((float*)val)[0],
					  ((float*)val)[1],
					  ((float*)val)[2]);
		}
    }
	else if (ft_strequ(prop, "axis"))
    {
		vec3f_normalize(val);
		if (ft_strequ(type, "cylinder"))
		{
			vec3f_set(&(obj->obj.cylinder->axis),
					  ((float*)val)[0],
					  ((float*)val)[1],
					  ((float*)val)[2]);
		}
		else if (ft_strequ(type, "plane"))
		{
			vec3f_set(&(obj->obj.plane->axis),
					  ((float*)val)[0],
					  ((float*)val)[1],
					  ((float*)val)[2]);
		}
		else
		{
			vec3f_set(&(obj->obj.cone->axis),
					  ((float*)val)[0],
					  ((float*)val)[1],
					  ((float*)val)[2]);
		}
    }
	else if (ft_strequ(prop, "radius") || ft_strequ(prop, "angle"))
		square_set(obj, prop, type, val);
	else if (ft_strequ(prop, "height"))
		obj->obj.cone->height = *((float*)val);
	else if (ft_strequ(prop, "reflection"))
		obj->reflection = *((float*)val);
	else if (ft_strequ(prop, "transparency"))
		obj->transparency = *((float*)val);
	if (ft_strequ(prop, "color"))
    {
		if (ft_strequ(type, "light"))
		{
			vec3f_set(&(obj->emission_color),
					  ((float*)val)[0],
					  ((float*)val)[1],
					  ((float*)val)[2]);
			vec3f_set(&(obj->surface_color), 0, 0, 0);
		}
		else 
		{
			vec3f_set(&(obj->surface_color),
					  ((float*)val)[0],
					  ((float*)val)[1],
					  ((float*)val)[2]);
			vec3f_set(&(obj->emission_color), 0, 0, 0);
		}
    }
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

int	object_intersect(t_obj *obj, t_ray *hit, float *t0)
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

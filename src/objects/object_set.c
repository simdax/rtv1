/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:54:35 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/03 12:07:06 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

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

void	object_set2(t_obj *obj, char *prop, char *type, void *val)
{
	if (ft_strequ(prop, "radius") || ft_strequ(prop, "angle"))
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
			vec3f_cpy(&(obj->emission_color), val);
			vec3f_set(&(obj->surface_color), 0, 0, 0);
		}
		else
		{
			vec3f_cpy(&(obj->surface_color), val);
			vec3f_set(&(obj->emission_color), 0, 0, 0);
		}
	}
}

void	object_set(t_obj *obj, char *prop, char *type, void *val)
{
	if (ft_strequ(prop, "position"))
	{
		obj->position = *((t_vec3f*)val);
		if (ft_strequ(type, "plane"))
			vec3f_cpy(&(obj->obj.plane->position), val);
		if (ft_strequ(type, "cone"))
			vec3f_cpy(&(obj->obj.cone->tip_position), val);
		else if (ft_strequ(type, "plane"))
			vec3f_cpy(&(obj->obj.sphere->center), val);
		else
			vec3f_cpy(&(obj->obj.sphere->center), val);
	}
	else if (ft_strequ(prop, "axis"))
	{
		vec3f_normalize(val);
		if (ft_strequ(type, "cylinder"))
			vec3f_cpy(&(obj->obj.cylinder->axis), val);
		else if (ft_strequ(type, "plane"))
			vec3f_cpy(&(obj->obj.plane->axis), val);
		else
			vec3f_cpy(&(obj->obj.cone->axis), val);
	}
	else
		object_set2(obj, prop, type, val);
}

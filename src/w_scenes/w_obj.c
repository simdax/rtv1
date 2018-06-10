/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_obj.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 18:18:24 by alerandy          #+#    #+#             */
/*   Updated: 2018/06/10 18:46:15 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	w_texture(t_obj *obj, int fd)
{
	if (obj->texture.type != TXT_NONE)
	{
		ft_putstr_fd(" texture (", fd);
		if (obj->texture.type == PATTERN)
		{
			ft_putstr_fd("pattern", fd);
			ft_putnbr_fd(obj->texture.pattern, fd);
		}
		else
			ft_putstr_fd(obj->texture.name, fd);
		ft_putstr_fd(")", fd);
	}
}

void	w_writingnolight(t_obj *obj, int fd)
{
	w_texture(obj, fd);
	if (obj->surface_color.x || obj->surface_color.y || obj->surface_color.z)
	{
		ft_putstr_fd("color (", fd);
		ft_putfloat_fd(obj->surface_color.x, 3, fd);
		ft_putstr_fd(" ", fd);
		ft_putfloat_fd(obj->surface_color.y, 3, fd);
		ft_putstr_fd(" ", fd);
		ft_putfloat_fd(obj->surface_color.z, 3, fd);
		ft_putstr_fd(")", fd);
	}
	if (obj->transparency)
	{
		ft_putstr_fd(" transparency (", fd);
		ft_putfloat_fd(obj->transparency, 3, fd);
		ft_putstr_fd(")", fd);
	}
	if (obj->reflection)
	{
		ft_putstr_fd(" reflection (", fd);
		ft_putfloat_fd(obj->reflection, 3, fd);
		ft_putstr_fd(")", fd);
	}
}

void	w_obj(t_obj *obj, int fd)
{
	if (!ft_strequ(obj->tag, "light"))
		w_writingnolight(obj, fd);
	else
	{
		ft_putstr_fd("color (", fd);
		ft_putfloat_fd(obj->emission_color.x, 3, fd);
		ft_putstr_fd(" ", fd);
		ft_putfloat_fd(obj->emission_color.y, 3, fd);
		ft_putstr_fd(" ", fd);
		ft_putfloat_fd(obj->emission_color.z, 3, fd);
		ft_putstr_fd(")", fd);
	}
	if (ft_strequ(obj->tag, "cylinder"))
	{
		ft_putstr_fd(" axis (", fd);
		ft_putfloat_fd(obj->obj.cylinder->axis.x, 3, fd);
		ft_putstr_fd(" ", fd);
		ft_putfloat_fd(obj->obj.cylinder->axis.y, 3, fd);
		ft_putstr_fd(" ", fd);
		ft_putfloat_fd(obj->obj.cylinder->axis.z, 3, fd);
		ft_putstr_fd(")", fd);
		ft_putstr_fd(" radius (", fd);
		ft_putfloat_fd(obj->obj.cylinder->radius, 3, fd);
		ft_putstr_fd(")", fd);
	}
}

void	w_obj2(t_obj *obj, int fd)
{
	if (ft_strequ(obj->tag, "cone"))
	{
		if (obj->obj.cone->axis.x || obj->obj.cone->axis.y || \
				obj->obj.cone->axis.z)
		{
			ft_putstr_fd(" axis (", fd);
			ft_putfloat_fd(obj->obj.cone->axis.x, 3, fd);
			ft_putstr_fd(" ", fd);
			ft_putfloat_fd(obj->obj.cone->axis.y, 3, fd);
			ft_putstr_fd(" ", fd);
			ft_putfloat_fd(obj->obj.cone->axis.z, 3, fd);
			ft_putstr_fd(")", fd);
		}
		if (obj->obj.cone->angle)
		{
			ft_putstr_fd(" angle (", fd);
			ft_putfloat_fd(obj->obj.cone->angle, 3, fd);
			ft_putstr_fd(")", fd);
		}
	}
}

void	w_obj3(t_obj *obj, int fd)
{
	if (ft_strequ(obj->tag, "sphere"))
	{
		if (obj->obj.sphere->radius)
		{
			ft_putstr_fd(" radius (", fd);
			ft_putfloat_fd(obj->obj.sphere->radius, 3, fd);
			ft_putstr_fd(")", fd);
		}
	}
	else if (ft_strequ(obj->tag, "plane"))
	{
		if (obj->obj.plane->axis.x || obj->obj.plane->axis.y || \
				obj->obj.plane->axis.z)
		{
			ft_putstr_fd(" axis (", fd);
			ft_putfloat_fd(obj->obj.plane->axis.x, 3, fd);
			ft_putstr_fd(" ", fd);
			ft_putfloat_fd(obj->obj.plane->axis.y, 3, fd);
			ft_putstr_fd(" ", fd);
			ft_putfloat_fd(obj->obj.plane->axis.z, 3, fd);
			ft_putstr_fd(")", fd);
		}
	}
}

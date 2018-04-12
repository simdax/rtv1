/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:35:22 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/12 17:32:14 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vec3f/vec3f.h"
# include "ray.h"
# include "resolvequadratics.h"
# include "sphere.h"
# include "cone.h"
# include "cylinder.h"
# include "plane.h"
# include "libft.h"

typedef struct		s_obj{
	char			*tag;
	union			u_type{
		t_sphere	*sphere;
		t_cone		*cone;
		t_plane		*plane;
		t_cylinder	*cylinder;
	}				obj;
	float			transparency;
	float			reflection;
	t_vec3f			surface_color;
	t_vec3f			emission_color;
	t_vec3f			position;
	void			*obj_ptr;
}					t_obj;

t_obj				object_new(char *type, char *parent);
void				del_object(void *c, size_t size);
void			object_del(void *el, size_t size);
void				object_set(t_obj *obj, char *type, char *prop, void *val);
void				object_print(t_obj *obj);
int					object_intersect(t_obj *obj, t_ray *hit,
								float *t0);
void				object_normale(t_obj *obj, t_ray *hit);
t_obj				**configure(char *config_file);

#endif

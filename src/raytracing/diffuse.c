/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:07:43 by scornaz           #+#    #+#             */
/*   Updated: 2018/05/16 17:00:25 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	intersection(int i, t_obj **objects, t_vec3f light_dir, t_ray *hit)
{
	double	solution;
	t_vec3f	orig;
	t_vec3f	normale;
	int		j;

	orig = hit->phit;
	normale = hit->nhit;
	vec3f_mul_unit2(&normale, BIAS);
	vec3f_add2(&orig, &normale);
	solution = BIAS;
	j = 0;
	while (objects[j])
	{
		if (i != j)
		{
			if (object_intersect(objects[j], &((t_ray){0,
								orig, light_dir}), &solution) &&
				solution < hit->max)
			{
				hit->transmission = 0;
				break ;
			}
		}
		++j;
	}
}

static double 	modulo(const double f)
{
  return (f - floor(f));
} 

static double	pattern(t_ray *hit)
{
  float angle = degreesToRadians(45);
  float s = hit->texture.x * cos(angle) - hit->texture.y * sin(angle);
  float t = hit->texture.y * cos(angle) + hit->texture.x * sin(angle);
  float scaleS = 20, scaleT = 20;
  //float pattern = (cos(hitTexCoordinates.y * 2 * M_PI * scaleT) * sin(hitTexCoordinates.x * 2 * M_PI * scaleS) + 1) * 0.5; // isect.hitObject->albedo
  //float pattern = (modulo(s * scaleS) < 0.5) ^ (modulo(t * scaleT) < 0.5);
  return (modulo(s * scaleS) < 0.5);
}

static void	set_surface(t_ray *hit, t_vec3f *light_direction,
						t_obj *object, t_vec3f *emission_light)
{
	double		diffuse;
	double		specular;
	t_vec3f		refraction;
	t_vec3f		object_surface_color;

	object_surface_color = object->surface_color;
	diffuse = fmax(0.0, vec3f_dot(&hit->nhit, light_direction));
	refraction = hit->nhit;
	vec3f_mul_unit2(&refraction, 2 * vec3f_dot(&hit->nhit, light_direction));
	vec3f_sub2(&refraction, light_direction);
	specular = fmax(0.0, vec3f_dot(&refraction, light_direction));
	specular = pow(specular, PHONG);
	if (NO_SHADOW || hit->transmission)
	{
	  //vec3f_mul_unit2(&object_surface_color, pattern(hit));
	  if (hit->texture.x)
	    {
	      t_vec3f tmp = object_get_texture_pixel(hit->texture.x, hit->texture.y, object);
	      //	  vec3f_print(&tmp);
	      vec3f_cpy(&object_surface_color, &tmp);
	    }
	  vec3f_mul2(&object_surface_color, emission_light);
	  vec3f_mul_unit2(&object_surface_color, diffuse);
	  if (SPEC && !ft_strequ("plane", object->tag))
	    vec3f_add_unit2(&object_surface_color, specular);
	  vec3f_add2(&hit->color, &object_surface_color);
	}
}

void		diffuse(t_obj **objects, t_obj *object, t_ray *hit)
{
	int		i;
	t_vec3f	light_direction;
	double	light_distance;

	hit->color = (t_vec3f){0, 0, 0};
	i = 0;
	while (objects[i])
	{
		if (objects[i]->emission_color.x || objects[i]->emission_color.y || \
				objects[i]->emission_color.z)
		{
			hit->transmission = 1;
			light_direction = objects[i]->position;
			vec3f_sub2(&light_direction, &hit->phit);
			hit->max = length(&light_direction);
			vec3f_normalize(&light_direction);
			intersection(i, objects, light_direction, hit);
			set_surface(hit, &light_direction, object,
						&(objects[i]->emission_color));
		}
		++i;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3f.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:09:59 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/10 20:28:33 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3F_H
# define VEC3F_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct	s_vec3f {
	float x;
	float y;
	float z;
}				t_vec3f;

typedef struct	s_33mat{
    t_vec3f	up;
    t_vec3f	right;
    t_vec3f	forward;
    t_vec3f	transpose;
}								t_33mat;

t_vec3f			*vec3f_new_unit (float x);
t_vec3f			*vec3f_new (float x, float y, float z);
void			vec3f_set (t_vec3f *vec3f, float x, float y, float z);
t_vec3f			*vec3f_normalize (t_vec3f *a);
t_vec3f			*vec3f_mul_unit (t_vec3f *a, float f);
t_vec3f			*vec3f_mul (t_vec3f *a, t_vec3f *b);
t_vec3f			*vec3f_sub (t_vec3f *a, t_vec3f *b);
t_vec3f			*vec3f_add (t_vec3f *a, t_vec3f *b);
t_vec3f			*vec3f_negate (t_vec3f *a);
t_vec3f			vec3f_cross(t_vec3f *a, t_vec3f *b);
float			vec3f_dot (t_vec3f *a, t_vec3f *b);
t_33mat	matrix_new(t_vec3f from, t_vec3f to, t_vec3f tmp);
t_vec3f	matrix_mul(t_33mat matrix, t_vec3f vector);
void matrix_print(t_33mat *matrix);
float			length2 (t_vec3f *a);
float			length (t_vec3f *a);
void			vec3f_print (t_vec3f *a);
void			vec3f_mul_unit2 (t_vec3f *a, float f);
void			vec3f_mul2 (t_vec3f *a, t_vec3f *b);
void			vec3f_add2 (t_vec3f *a, t_vec3f *b);
void			vec3f_add_unit2 (t_vec3f *a, float b);
void			vec3f_sub2 (t_vec3f *a, t_vec3f *b);
void			vec3f_cpy (t_vec3f *a, t_vec3f *b);
void			vec3f_normalize2(t_vec3f *a);

#endif

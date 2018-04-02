/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fff.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:38:06 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/02 15:28:38 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FFF_H
# define FFF_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct	s_vec3f {
	float x;
	float y;
	float z;
}				t_vec3f;

t_vec3f			*vec3f_new_unit (float x);
t_vec3f			*vec3f_new (float x, float y, float z);
void   			vec3f_set (t_vec3f *vec3f, float x, float y, float z);
void   			vec3f_normalize (t_vec3f *a);
void   			vec3f_mul_unit (t_vec3f *a, float f);
void   			vec3f_mul (t_vec3f *a, t_vec3f *b);
void   			vec3f_mul_inplace (t_vec3f *a, t_vec3f *b);
void   			vec3f_sub (t_vec3f *a, t_vec3f *b);
void   			vec3f_add (t_vec3f *a, t_vec3f *b);
void   			vec3f_add_inplace (t_vec3f *a, t_vec3f *b);
void   			vec3f_negate (t_vec3f *a);
float  			vec3f_dot (t_vec3f *a, t_vec3f *b);
float  			length2 (t_vec3f *a);
float  			length (t_vec3f *a);
void   			vec3f_print (t_vec3f *a);

#endif

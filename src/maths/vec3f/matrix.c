/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:09:32 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/10 20:35:16 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3f.h"

t_vec3f	vec3f_cross(t_vec3f *a, t_vec3f *b)
{
    return (t_vec3f){
        a->y * b->z - a->z * b->y,
            a->z * b->x - a->x * b->z,
            a->x * b->y - a->y * b->x
            };
}

t_33mat	matrix_new(t_vec3f from, t_vec3f to, t_vec3f tmp)
{
    t_33mat	matrix;

    matrix.transpose = from;
    matrix.forward = to;
    vec3f_normalize(&matrix.forward);
    matrix.right = vec3f_cross(&tmp, &matrix.forward);
    matrix.up = vec3f_cross(&matrix.forward, &matrix.right);
    return (matrix);
}

t_vec3f	matrix_mul(t_33mat matrix, t_vec3f vector)
{
   return (t_vec3f){
       matrix.transpose.x + (matrix.right.x * vector.x + matrix.up.x * vector.y
                             + matrix.forward.x * vector.z),
           matrix.transpose.y + (matrix.right.y * vector.x + matrix.up.y * vector.y
                                 + matrix.forward.y * vector.z),
           matrix.transpose.z + (matrix.right.z * vector.x + matrix.up.z * vector.y
                                 + matrix.forward.z * vector.z),
           };
}

void matrix_print(t_33mat *matrix)
{
    printf("up, right, forward\n");
    vec3f_print(&matrix->up);
    vec3f_print(&matrix->right);
    vec3f_print(&matrix->forward);
}

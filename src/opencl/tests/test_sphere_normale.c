/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sphere_normale.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 13:41:49 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/17 14:02:25 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "libft.h"
#include "opengpu.h"

typedef struct	s_vec3f {
	double x;
	double y;
	double z;
}		t_vec3f;

typedef struct	s_hit{
	double		tnear;
	t_vec3f		rayorig;
	t_vec3f		raydir;
	int		obj_index;
	t_vec3f		nhit;
	t_vec3f		phit;
	t_vec3f		color;
	t_vec3f		distance;
	int		inside;
	double		transmission;
	t_vec3f		refldir;
	t_vec3f		refraction;
	double		facingratio;
	t_vec3f		cp;
	double		max;
}		t_ray;

typedef struct	s_sphere {
	t_vec3f		center;
	double		radius;
	double		radius2;
}		t_sphere;


int			main(void)
{
	t_cl		gpu;
	t_program	addvec;
	t_sphere	sphere = (t_sphere){(t_vec3f){0, 2, 2}, 4, 16};
	t_ray		ray = (t_ray){0, (t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0}, 0, (t_vec3f){5, 5, 5}};
	t_vec3f		vo;
	size_t		work_size[1];

	work_size[0]= 1;
	gpu = create_context();
	addvec = create_program("grosse_math.cl", "sphere_normale", 3, &gpu, \
				INPUT, sizeof(t_sphere), &sphere,
				INPUT, sizeof(t_ray), &ray,
				OUTPUT, sizeof(t_vec3f), &vo);
	clEnqueueNDRangeKernel(gpu.queue, addvec.kernel, 1, 0, work_size, 0, 0, \
		0, 0);
	clEnqueueReadBuffer(gpu.queue, addvec.buffers[2], CL_TRUE, 0, \
		sizeof(t_vec3f), &vo, 0, NULL, NULL);
	printf("x: %f, y: %f, z: %f\n", vo.x, vo.y, vo.z);
	erase_program(&addvec, 3);
	erase_context(&gpu);
	return (0);
}

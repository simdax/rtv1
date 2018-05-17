/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 02:33:36 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/16 12:31:48 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "libft.h"
#include "opengpu.h"
#include "sphere.h"
#include "ray.h"

int			main(void)
{
	t_cl		gpu;
	t_program	addvec;
	t_sphere	sphere = (t_sphere){(t_vec3f){0, 0, -4}, 4, 16};
	t_ray		ray = (t_ray){INFINITY, (t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0}};
	double		sol = 456;
	size_t work_size[1];
	  work_size[0]= 1;
	gpu = create_context();
	addvec = create_program("grosse_math.cl", "sphere_intersect", 3, &gpu, \
		INPUT, sizeof(t_sphere), &sphere, \
		INPUT, sizeof(t_ray), &ray, \
		OUTPUT, sizeof(double), &sol);
	clEnqueueNDRangeKernel(gpu.queue, addvec.kernel, 1, work_size, 0, 0, 0, \
		0, 0);
	clEnqueueReadBuffer(gpu.queue, addvec.buffers[2], CL_TRUE, 0, \
		sizeof(double), &sol, 0, NULL, NULL);
	printf("solution : %f\n", sol);
	erase_program(&addvec, 3);
	erase_context(&gpu);
	return (0);
}

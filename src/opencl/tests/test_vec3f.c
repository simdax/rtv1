/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 02:33:36 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/16 09:51:33 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "./libft/libft.h"
#include "opengpu.h"

typedef struct	s_vec3f {
	double x;
	double y;
	double z;
}				t_vec3f;

int			main(void)
{
	t_cl		gpu;
	t_program	addvec;
	size_t		work_size[1];
	t_vec3f		v1;
	t_vec3f		v2;
	t_vec3f		vo;

	work_size[0] = 1;
	v1.x = 10;
	v1.y = 25;
	v1.z = -5;
	v2.x = 50;
	v2.y = -10;
	v2.z = 42;
	printf("vec1\tx: %f\ty: %f\tz: %f\n", v1.x, v1.y, v1.z);
	printf("vec2\tx: %f\ty: %f\tz: %f\n", v2.x, v2.y, v2.z);
	gpu = create_context();
	addvec = create_program("vec3f.cl", "add_vec3f", 3, &gpu, \
		INPUT, sizeof(t_vec3f), &v1, \
		INPUT, sizeof(t_vec3f), &v2, \
		OUTPUT, sizeof(t_vec3f), &vo);
	clEnqueueNDRangeKernel(gpu.queue, addvec.kernel, 1, 0, work_size, 0, 0, \
		0, 0);
	clEnqueueReadBuffer(gpu.queue, addvec.buffers[2], CL_TRUE, 0, \
		sizeof(t_vec3f), &vo, 0, NULL, NULL);
	printf("vec_out\tx: %f\ty: %f\tz: %f\n", vo.x, vo.y, vo.z);
	erase_program(&addvec, 2);
	erase_context(&gpu);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 02:33:36 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/16 11:38:37 by acourtin         ###   ########.fr       */
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
}				t_vec3f;

int			main(void)
{
	t_cl		gpu;
	t_program	addvec;
	size_t		work_size[1];
	double		d;
	t_vec3f		v1;
	t_vec3f		v2;
	t_vec3f		vo;

	work_size[0] = 1;
	v1.x = 1;
	v1.y = 25;
	v1.z = -5;
	v2.x = 10;
	v2.y = 25;
	v2.z = -5;
	d = 4564;
	printf("vec1\tx: %f\ty: %f\tz: %f\n", v1.x, v1.y, v1.z);
	gpu = create_context();
	addvec = create_program("vec3f.cl", "vec3f_normalize", 2, &gpu, \
		INPUT, sizeof(t_vec3f), &v1, \
		OUTPUT, sizeof(t_vec3f), &v1);
	clEnqueueNDRangeKernel(gpu.queue, addvec.kernel, 1, 0, work_size, 0, 0, \
		0, 0);
	clEnqueueReadBuffer(gpu.queue, addvec.buffers[1], CL_TRUE, 0, \
		sizeof(t_vec3f), &v1, 0, NULL, NULL);
	printf("vec1\tx: %f\ty: %f\tz: %f\n", v1.x, v1.y, v1.z);
	erase_program(&addvec, 2);
	erase_context(&gpu);
	return (0);
}

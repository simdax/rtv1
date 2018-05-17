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

typedef struct	s_vec3f {
	double x;
	double y;
	double z;
}				t_vec3f;

int			main(void)
{
	t_cl		gpu;
	t_program	addvec;
	int nb_vec = 10;
	size_t		work_size[1];
	t_vec3f		v1[nb_vec];

	for(int i = 0; i < nb_vec; ++i)
		v1[i] = (t_vec3f){i + i, i + 1, i + 1};
	work_size[0] = nb_vec;
	gpu = create_context();
	// //for(int i = 0; i < nb_vec; ++i)
	// 	printf("vec1\tx: %f\ty: %f\tz: %f\n", v1[i].x, v1[i].y, v1[i].z);
	addvec = create_program("vec3f.cl", "vec3f_normalize2", 2, &gpu, \
		INPUT, nb_vec * sizeof(t_vec3f), &v1, \
		OUTPUT, nb_vec * sizeof(t_vec3f), &v1);
	clEnqueueNDRangeKernel(gpu.queue, addvec.kernel, 1, 0, work_size, 0, 0, \
		0, 0);
	clEnqueueReadBuffer(gpu.queue, addvec.buffers[1], CL_TRUE, 0, \
		nb_vec * sizeof(t_vec3f), &v1, 0, NULL, NULL);
	for(int i = 0; i < nb_vec; ++i)
		printf("vec1\tx: %f\ty: %f\tz: %f\n", v1[i].x, v1[i].y, v1[i].z);
	erase_program(&addvec, 2);
	erase_context(&gpu);
	return (0);
}

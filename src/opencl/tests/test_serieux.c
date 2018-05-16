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
	int nb_vec = 1;
	size_t		work_size[1];
	double		sol;
	t_vec3f		v1[nb_vec];

	for(int i = 0; i < nb_vec; ++i)
		v1[i] = (t_vec3f){3, 5, -2};
	work_size[0] = nb_vec;
	gpu = create_context();
	addvec = create_program("grosse_math.cl", "length2", 2, &gpu, \
		INPUT, nb_vec * sizeof(t_vec3f), &v1, \
		OUTPUT, nb_vec * sizeof(double), &sol);
	clEnqueueNDRangeKernel(gpu.queue, addvec.kernel, 1, 0, work_size, 0, 0, \
		0, 0);
	clEnqueueReadBuffer(gpu.queue, addvec.buffers[1], CL_TRUE, 0, \
		nb_vec * sizeof(double), &sol, 0, NULL, NULL);
	for(int i = 0; i < nb_vec; ++i)
		printf("solution : %f\n", 4650.45);
	erase_program(&addvec, 2);
	erase_context(&gpu);
	return (0);
}

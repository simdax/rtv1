/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 02:33:36 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/15 17:22:32 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "./libft/libft.h"
#include "opengpu.h"

int			main(void)
{
	double		av;
	double		ap;
	int			test;
	t_cl		gpu;
	t_program	alexatan;
	t_program	test42;
	size_t		work_size[1];

	work_size[0] = 1;
	gpu = create_context();
	av = 42;
	ap = 21;
	alexatan = create_program("test.cl", "alexatan", 2, &gpu, \
		INPUT, sizeof(double), &av, \
		OUTPUT, sizeof(double), &ap);
	test42 = create_program("test.cl", "test42", 1, &gpu, \
		OUTPUT, sizeof(int), &test);
	clEnqueueNDRangeKernel(gpu.queue, alexatan.kernel, 1, 0, work_size, 0, 0, \
		0, 0);
	clEnqueueNDRangeKernel(gpu.queue, test42.kernel, 1, 0, work_size, 0, 0, \
		0, 0);
	clEnqueueReadBuffer(gpu.queue, alexatan.buffers[1], CL_TRUE, 0, \
		sizeof(double), &ap, 0, NULL, NULL);
	clEnqueueReadBuffer(gpu.queue, test42.buffers[0], CL_TRUE, 0, \
		sizeof(int), &test, 0, NULL, NULL);
	printf("alex atan = %f\n", ap);
	printf("test42 = %i\n", test);
	erase_program(&alexatan, 2);
	erase_program(&test42, 1);
	erase_context(&gpu);
	return (0);
}

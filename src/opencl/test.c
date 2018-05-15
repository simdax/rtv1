/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 02:33:36 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/15 03:33:18 by acourtin         ###   ########.fr       */
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
	double av;
	double ap;
	t_cl gpu;
	t_program alexatan;
	size_t		work_size[1];

	work_size[0] = 1;
	av = 42;
	gpu = create_context();
	alexatan = create_program("test.cl", "alexatan", 2, &gpu, \
		INPUT, sizeof(double), &av, \
		OUTPUT, sizeof(double), &ap);
	clEnqueueNDRangeKernel(gpu.queue, alexatan.kernel, 1, 0, work_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(gpu.queue, alexatan.buffers[1], CL_TRUE, 0, \
		sizeof(double), &ap, 0, NULL, NULL);
	printf("%f\n", ap);
	erase_program(&alexatan, 2);
	erase_context(&gpu);
	return (0);
}

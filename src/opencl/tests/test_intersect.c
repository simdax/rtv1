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

int			main(void)
{
	t_cl		gpu;
	t_program	addvec;
	t_sphere	sphere = (t_sphere){(t_vec3f){0, 0, -4};
					    4, 16};

	work_size[0] = nb_vec;
	gpu = create_context();
	addvec = create_program("all.cl", "sphere_intersect", 2, &gpu, \
		INPUT, nb_vec * sizeof(t_vec3f), &v1, \
		OUTPUT, nb_vec * sizeof(double), &sol);
	clEnqueueNDRangeKernel(gpu.queue, addvec.kernel, 1, 0, work_size, 0, 0, \
		0, 0);
	clEnqueueReadBuffer(gpu.queue, addvec.buffers[1], CL_TRUE, 0, \
		nb_vec * sizeof(double), &sol, 0, NULL, NULL);
	for(int i = 0; i < nb_vec; ++i)
		printf("solution : %f\n", sol);
	erase_program(&addvec, 2);
	erase_context(&gpu);
	return (0);
}

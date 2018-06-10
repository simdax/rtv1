/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:40:44 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/16 12:13:12 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"
#include "opengpu.h"

t_cl		create_context(void)
{
	t_cl	gpu;

	clGetPlatformIDs(1, &gpu.platform, NULL);
	clGetDeviceIDs(gpu.platform, CL_DEVICE_TYPE_ALL, 1, &gpu.device, NULL);
	gpu.context = clCreateContext(0, 1, &gpu.device, NULL, NULL, NULL);
	gpu.queue = clCreateCommandQueue(gpu.context, gpu.device, 0, 0);
	return (gpu);
}

int		init_program(t_program *prog, t_buffer **s_buffers, \
	int n_buffers, char *filename)
{
	if (!(prog->source = readcl(filename, &prog->source_size)))
		return (0);
	if (!(prog->buffers = ft_memalloc(sizeof(cl_mem) * n_buffers)))
		return (0);
	if (!(*s_buffers = ft_memalloc(sizeof(t_buffer) * n_buffers)))
		return (0);
	return (1);
}

void		create_buffers(t_program *prog, t_buffer *s_buffers, \
	int n_buffers, t_cl *gpu)
{
	int	i;

	i = -1;
	while (++i < n_buffers)
	{
		if (s_buffers[i].type == INPUT)
			prog->buffers[i] = clCreateBuffer(gpu->context, CL_MEM_READ_ONLY |
				CL_MEM_COPY_HOST_PTR, s_buffers[i].size, s_buffers[i].name, 0);
		else
			prog->buffers[i] = clCreateBuffer(gpu->context, CL_MEM_WRITE_ONLY,
				s_buffers[i].size, 0, 0);
	}
	prog->program = clCreateProgramWithSource(gpu->context, prog->source_size,
						  (const char**)prog->source, 0, 0);
	clBuildProgram(prog->program, 0, NULL, NULL, NULL, NULL);
}

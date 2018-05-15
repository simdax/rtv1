/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:40:44 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/15 03:45:44 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
// A EFFACER
#include <stdio.h>
// ---
#include <stdlib.h>
#include <stdarg.h>
#include "./libft/libft.h"
#include "opengpu.h"

t_cl			create_context(void)
{
	t_cl	gpu;

	clGetPlatformIDs(1, &gpu.platform, NULL);
	clGetDeviceIDs(gpu.platform, CL_DEVICE_TYPE_ALL, 1, &gpu.device, NULL);
	gpu.context = clCreateContext(0, 1, &gpu.device, NULL, NULL, NULL);
	gpu.queue = clCreateCommandQueue(gpu.context, gpu.device, 0, 0);
	return (gpu);
}

static int		init_program(t_program *prog, t_buffer **s_buffers, \
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

static void		create_buffers(t_program *prog, t_buffer *s_buffers, \
	int n_buffers, t_cl *gpu)
{
	int			i;

	i = -1;
	while (++i < n_buffers)
	{
		if (s_buffers[i].type == INPUT)
			prog->buffers[i] = clCreateBuffer(gpu->context, CL_MEM_READ_ONLY |
				CL_MEM_COPY_HOST_PTR, s_buffers[i].size, &s_buffers[i].name, 0);
		else
			prog->buffers[i] = clCreateBuffer(gpu->context, CL_MEM_WRITE_ONLY,
				s_buffers[i].size, 0, 0);
	}
	prog->program = clCreateProgramWithSource(gpu->context, prog->source_size,
		(const char**)prog->source, 0, 0);
	clBuildProgram(prog->program, 0, NULL, NULL, NULL, NULL);
}

t_program		create_program(char *filename, char *func_name, int n_buffers, \
	t_cl *gpu, ...)
{
	va_list		ap;
	t_program	prog;
	t_buffer	*s_buffers;
	int			i;

	init_program(&prog, &s_buffers, n_buffers, filename);
	i = -1;
	va_start(ap, gpu);
	while (++i < n_buffers)
	{
		s_buffers[i].type = va_arg(ap, t_type_buf);
		s_buffers[i].size = va_arg(ap, size_t);
		s_buffers[i].name = va_arg(ap, void*);
	}
	va_end(ap);
	create_buffers(&prog, s_buffers, n_buffers, gpu);
	prog.kernel = clCreateKernel(prog.program, func_name, NULL);
	if (!prog.kernel)
	{
		printf("!!! Erreur compilation du script %s !!!\n", filename);
	}
	i = -1;
	while (++i < n_buffers)
		clSetKernelArg(prog.kernel, i, sizeof(cl_mem), \
			(void *)&prog.buffers[i]);
	free(s_buffers);
	printf("Script %s OK !!\n", filename);
	return (prog);
}

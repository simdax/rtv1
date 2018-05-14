/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erasecl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:48:55 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/14 19:32:23 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libft/libft.h"
#include "opengpu.h"

void			erase_context(t_cl *gpu)
{
	clReleaseCommandQueue(gpu->queue);
	clReleaseContext(gpu->context);
}

void			erase_program(t_program *prog, int n_buffers)
{
	int			i;

	clReleaseKernel(prog->kernel);
	clReleaseProgram(prog->program);
	i = -1;
	while (++i < n_buffers)
		clReleaseMemObject(prog->buffers[i]);
	free(prog->source);
	free(prog->buffers);
}

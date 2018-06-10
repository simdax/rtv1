#include <stdio.h>
#include "opengpu.h"

t_program		create_program(char *filename, char *func_name, int n_buffers, \
	t_cl *gpu, ...)
{
	va_list		ap;
	t_program	prog;
	t_buffer	*s_buffers;
	int		i;

	if (!(init_program(&prog, &s_buffers, n_buffers, filename)))
		exit(0);
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
	if (!(prog.kernel = clCreateKernel(prog.program, func_name, &prog.err)))
		printf("\e[31mERREUR MEC !!!!:\n\n%s\e[0m\n\n", geterrorstring(prog.err));
	i = -1;
	while (++i < n_buffers)
		clSetKernelArg(prog.kernel, i, sizeof(cl_mem), (void *)&prog.buffers[i]);
	free(s_buffers);
	return (prog);
}

t_program		create_program2(char *filename, char *func_name, int n_buffers, \
	t_cl *gpu, va_list ap)
{
	t_program	prog;
	t_buffer	*s_buffers;
	int		i;

	if (!(init_program(&prog, &s_buffers, n_buffers, filename)))
		exit(0);
	i = -1;
	while (++i < n_buffers)
	{
		s_buffers[i].type = va_arg(ap, t_type_buf);
		s_buffers[i].size = va_arg(ap, size_t);
		s_buffers[i].name = va_arg(ap, void*);
	}
	create_buffers(&prog, s_buffers, n_buffers, gpu);
	if (!(prog.kernel = clCreateKernel(prog.program, func_name, &prog.err)))
		printf("\e[31mERREUR MEC !!!!:\n\n%s\e[0m\n\n", geterrorstring(prog.err));
//	char	buffer[2048];
//	size_t	l;
//	clGetProgramBuildInfo(prog->program, gpu->device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &l);
//	printf("fsadjfhsda for %zd %s", l, buffer);
	i = -1;
	while (++i < n_buffers)
		clSetKernelArg(prog.kernel, i, sizeof(cl_mem), (void *)&prog.buffers[i]);
	free(s_buffers);
	return (prog);
}

t_program		create_program3(t_cl *gpu, char *filename, char *func_name,
					int n_buffers, va_list ap, t_ret_val ret)
{
	t_program	prog;
	t_buffer	*s_buffers;
	int		i;

	if (!(init_program(&prog, &s_buffers, n_buffers + 1, filename)))
		exit(0);
	i = -1;
	while (++i < n_buffers)
	{
		s_buffers[i].type = INPUT;
		s_buffers[i].size = va_arg(ap, size_t);
		s_buffers[i].name = va_arg(ap, void*);
	}
	s_buffers[i].type = OUTPUT;
	s_buffers[i].size = ret.size;
	s_buffers[i].name = ret.val;
	create_buffers(&prog, s_buffers, n_buffers + 1, gpu);
	if (!(prog.kernel = clCreateKernel(prog.program, func_name, &prog.err)))
		printf("\e[31mERREUR MEC !!!!:\n\n%s\e[0m\n\n", geterrorstring(prog.err));
	i = -1;
	while (++i < (n_buffers + 1))
		clSetKernelArg(prog.kernel, i, sizeof(cl_mem), (void *)&prog.buffers[i]);
	free(s_buffers);
	return (prog);
}

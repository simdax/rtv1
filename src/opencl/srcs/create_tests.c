#include "stdarg.h"
#include "opengpu.h"
#include <stdio.h>

int	cl_create_test(char *file, char *func, void *val, size_t val_size, int nb, ...)
{
	t_cl		gpu;
	t_program	addvec;
	size_t		work_size[1];
	va_list		args;

	work_size[0]= 1;
	gpu = create_context();
	va_start(args, nb);
	addvec = create_program2(file, func, nb, &gpu, args);
	va_end(args);
	clEnqueueNDRangeKernel(gpu.queue, addvec.kernel, 1, 0, work_size, 0, 0, \
		0, 0);
	clEnqueueReadBuffer(gpu.queue, addvec.buffers[nb - 1], CL_TRUE, 0, \
		val_size, val, 0, NULL, NULL);
	erase_program(&addvec, nb);
	erase_context(&gpu);
	return (0);
}

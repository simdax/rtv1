/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengpu.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:44:02 by acourtin          #+#    #+#             */
/*   Updated: 2018/06/10 13:31:59 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGPU_H
# define OPENGPU_H

# include <OpenCL/opencl.h>

typedef struct			s_cl
{
	cl_device_id		device;
	cl_platform_id		platform;
	cl_context			context;
	cl_command_queue	queue;
}						t_cl;

typedef struct			s_program
{
	int					source_size;
	cl_mem				*buffers;
	cl_program			program;
	cl_kernel			kernel;
	char				**source;
	int					err;
}						t_program;

typedef enum			e_type_buf
{
	INPUT,
	OUTPUT
}						t_type_buf;

typedef struct			s_buffer
{
	t_type_buf			type;
	size_t				size;
	void				*name;
}						t_buffer;

typedef struct			s_ret_val
{
  	size_t		size;
	void		*val;
  	size_t		work_size;
}				t_ret_val;

char			**readcl(char *source, int *i);
t_cl			create_context(void);
void			erase_context(t_cl *gpu);
void			erase_program(t_program *prog, int n_buffers);
int			init_program(t_program *prog, t_buffer **s_buffers,
			     int n_buffers, char *filename);
void			create_buffers(t_program *prog, t_buffer *s_buffers,
			       int n_buffers, t_cl *gpu);
const char		*geterrorstring(cl_int error);
int			cl_create_test(char *file, char *func, void *val, size_t val_size, int nb, ...);
int			cl_create_test2(char *file, char *func,
					t_ret_val res, int nb, ...);
t_program		create_program(char *filename, char *func_name,
				       int n_buffers, t_cl *gpu, ...);
t_program		create_program2(char *filename, char *func_name,
					int n_buffers, t_cl *gpu, va_list va);
t_program		create_program3(t_cl *gpu, char *filename, char *func_name,
					int n_buffers, va_list ap, t_ret_val ret);

#endif

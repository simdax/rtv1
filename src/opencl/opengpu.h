/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengpu.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:44:02 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/14 18:55:02 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGPU_H
# define OPENGPU_H

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
	void 				*name;
}						t_buffer;

char					**readcl(char *source, int *i);
t_cl					create_context(void);
t_program				create_program(char *filename, char *func_name, int n_buffers, \
	t_cl *gpu, ...);
void					erase_context(t_cl *gpu);
void					erase_program(t_program *prog, int n_buffers);

#endif

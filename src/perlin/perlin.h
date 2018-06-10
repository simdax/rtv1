/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:07:46 by scornaz           #+#    #+#             */
/*   Updated: 2018/06/10 13:16:44 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERLIN_H
# define PERLIN_H

typedef struct	s_perlin{
	int				varia;
	unsigned		width;
	unsigned		height;
	float			*image;
	unsigned char	*pixels;
	float			*(*gen_f)(size_t t);
}				t_perlin;

t_perlin		*perlin_new(unsigned width, unsigned height, unsigned varia);
void			perlin_free(t_perlin **perlin);
void			perlin_write_image(t_perlin *perlin, char *path);
float			*perlin_generate(size_t size);
float			*perlin_generate2(size_t h, size_t w);
#endif

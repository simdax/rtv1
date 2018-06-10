/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:10:52 by scornaz           #+#    #+#             */
/*   Updated: 2018/06/10 13:30:56 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "opengpu.h"
#include "mem.h"
#include "perlin.h"

int		main(void)
{
	unsigned char	*pixels;
	t_perlin		*perlin;
	int				i;

	perlin = perlin_new(500, 500, 100);
	perlin_write_image(perlin, "perlin.ppm");
	perlin_free(&perlin);
}

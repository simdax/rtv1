/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:10:52 by scornaz           #+#    #+#             */
/*   Updated: 2018/06/10 14:22:31 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "opengpu.h"
#include "mem.h"
#include "perlin.h"

int		main(void)
{
	t_perlin		*perlin;

	perlin = perlin_new(500, 500, 100, "perlin.cl");
	perlin_write_image(perlin, "perlin.ppm");
	perlin_free(&perlin);
}

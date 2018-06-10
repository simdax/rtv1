/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:17:26 by scornaz           #+#    #+#             */
/*   Updated: 2018/06/10 13:25:29 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opengpu.h"
#include <stdio.h>
#include "perlin.h"
#include "mem.h"

const float g_permutation[] = { 151, 160, 137, 91, 90, 15,
								131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
								36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10,
								23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197,
								62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177,
								33,	88, 237, 149, 56, 87, 174, 20, 125, 136,
								171, 168, 68, 175, 74, 165, 71, 134, 139, 48,
								27, 166, 77, 146, 158, 231, 83, 111, 229, 122,
								60, 211, 133, 230, 220, 105, 92, 41, 55, 46,
								245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1,
								216, 80, 73, 209, 76, 132, 187, 208, 89, 18,
								169, 200, 196, 135, 130, 116, 188, 159, 86, 164,
								100, 109, 198, 173, 186, 3, 64, 52, 217, 226,
								250, 124, 123, 5, 202, 38, 147, 118, 126, 255,
								82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17,
								182, 189, 28, 42, 223, 183, 170, 213, 119, 248,
								152, 2, 44, 154, 163, 70, 221, 153, 101, 155,
								167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108,
								110, 79, 113, 224, 232, 178, 185, 112, 104, 218,
								246, 97, 228, 251, 34, 242, 193, 238, 210, 144,
								12, 191, 179, 162, 241, 81, 51, 145, 235, 249,
								14, 239, 107, 49, 192, 214, 31, 181, 199, 106,
								157, 184, 84, 204, 176, 115, 121, 50, 45, 127,
								4, 150, 254, 138, 236, 205, 93, 222, 114, 67,
								29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61,
								156, 180 };

float	*perlin_generate(size_t size)
{
	t_ret_val	ret;
	double		*points3d;
	float		*res;
	int			y;
	int			x;

	points3d = ft_memalloc(sizeof(double) * size * 4);
	res = ft_memalloc(sizeof(float) * size);
	y = 0;
	while (y < size)
    {
		x = 0;
		while (x < 4)
		{
			if (x == 0)
				points3d[y * 4 + x] = 0.1;
			else if (x == 1)
				points3d[y * 4 + x] = y;
			else if (x == 2)
				points3d[y * 4 + x] = (double)(y * 4 + x) / 500;
			else
				points3d[y * 4 + x] = 10;
			++x;
		}
		++y;
    };
	ret = (t_ret_val){sizeof(float) * size, res, size};
	cl_create_test2("perlin.cl", "gradient_noise_d", ret, 2,
					sizeof(g_permutation), &g_permutation,
					sizeof(double) * size * 4, points3d);
	free(points3d);
	return (res);
}

/* float	*perlin_generate2(size_t h, size_t w) */
/* { */
/* 	t_ret_val	ret; */
/* 	float		*points3d; */
/* 	float		*res; */
/* 	int			y; */
/* 	int			x; */

/* 	points3d = ft_memalloc(sizeof(float) * size * 4); */
/* 	float slice = 4; */
/* 	ret = (t_ret_val){sizeof(float) * size, res, size}; */
/* 	cl_create_test2("Noise.cl", "RandomTest", points3d, 5, */
/* 					sizeof(int), &w, */
/* 					sizeof(int), &h, */
/* 					sizeof(float), &w, */
/* 					sizeof(float), &h, */
/* 					sizeof(float), &slice); */
/* 	return (points3d); */
/* } */

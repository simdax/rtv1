/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:03:04 by cbesse            #+#    #+#             */
/*   Updated: 2018/03/05 15:03:07 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		my_key_funct(int keycode)
{
	if (keycode == 53)
		exit(1);
	return (0);
}

void	mlx_set(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W_LENGHT, W_WIDTH, "RTv1");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx, W_LENGHT, W_WIDTH);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
			&mlx->img.size_l, &mlx->img.endian);
}

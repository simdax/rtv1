/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 11:48:33 by acourtin          #+#    #+#             */
/*   Updated: 2018/06/03 14:14:26 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rtv1.h"

void			filters_names(char *filter[10])
{
	filter[0] = "Return";
	filter[1] = "None";
	filter[2] = "Sepia";
	filter[3] = "Grayscale";
	filter[4] = "Warm";
	filter[5] = "Contrast";
	filter[6] = "Blueish";
	filter[7] = "Negative";
	filter[8] = "FXAA";
	filter[9] = "Cartoon";
}

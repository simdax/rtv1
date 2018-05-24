/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:52:22 by cbesse            #+#    #+#             */
/*   Updated: 2018/04/10 18:05:26 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vecteur	libe(void **r, double *min_max, t_vecteur vr)
{
	ft_memdel(r);
	free(min_max);
	return (vr);
}

void		set_min_max(double min, double max, double *min_max)
{
	min_max[0] = min;
	min_max[1] = max;
}

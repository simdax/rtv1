/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 08:42:34 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/12 08:51:11 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		btn_clean(t_button **btns)
{
	int		i;

	i = -1;
	if (btns)
	{
		while (btns[++i])
		{
			ttf_destroy(btns[i]->t);
			free(btns[i]);
		}
		free(btns);
	}
}

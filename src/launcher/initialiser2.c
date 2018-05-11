/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialiser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:57:37 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/10 15:25:19 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		set_msbtns2(t_launch *launcher, t_button **buttons, \
		t_texture **textures)
{
	buttons[2] = button_new(35, 350, 175, 36);
	buttons[2]->func = &reset_resolution;
	buttons[2]->param = (void*)launcher;
	buttons[2]->texture = textures[1];
	buttons[2]->t = ttf_newb(launcher->render, "Reset", buttons[2], \
			"assets/28 Days Later.ttf");
	buttons[3] = button_new(235, 350, 175, 36);
	buttons[3]->func = &change_resolution_min;
	buttons[3]->param = (void*)launcher;
	buttons[3]->texture = textures[1];
	buttons[3]->t = ttf_newb(launcher->render, "800 X 600", buttons[3], \
			"assets/28 Days Later.ttf");
	buttons[4] = button_new(435, 350, 175, 36);
	buttons[4]->func = &change_resolution_max;
	buttons[4]->param = (void*)launcher;
	buttons[4]->texture = textures[1];
	buttons[4]->t = ttf_newb(launcher->render, "1280 X 720", buttons[4], \
			"assets/28 Days Later.ttf");
}
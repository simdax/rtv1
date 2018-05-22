/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_obj.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:06:40 by alerandy          #+#    #+#             */
/*   Updated: 2018/05/21 19:55:43 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef L_OBJ_H
# define L_OBJ_H

# include "interface.h"

void		l_plan(t_sdl *sdl, t_plane *obj);
void		l_cone(t_sdl *sdl, t_cone *obj);
void		l_cyli(t_sdl *sdl, t_cylinder *obj);
void		l_sphe(t_sdl *sdl, t_sphere *obj);

#endif

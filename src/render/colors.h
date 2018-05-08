/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:16:40 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/08 13:04:43 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "rtv1.h"

typedef struct		s_clr
{
	int				r;
	int				g;
	int				b;
}					t_clr;

typedef enum		e_cfilter
{
	NONE,
	SEPIA
}					t_cfilter;

void				change_colors(t_render_opts *opts, t_cfilter f);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:16:40 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/10 19:12:45 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

typedef struct		s_clr
{
	int				r;
	int				g;
	int				b;
}					t_clr;

typedef enum		e_cfilter
{
	NONE,
	SEPIA,
	GRAYSCALE,
	NEGATIVE
}					t_cfilter;

#endif

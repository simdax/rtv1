/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <acourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:16:40 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/21 11:37:22 by acourtin         ###   ########.fr       */
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

typedef struct		s_mclr
{
	t_clr			ce;
	t_clr			up;
	t_clr			dn;
	t_clr			le;
	t_clr			ri;
	t_clr			res;
	int				okup;
	int				okdn;
	int				okle;
	int				okri;
}					t_mclr;

typedef enum		e_cfilter
{
	NONE,
	SEPIA,
	GRAYSCALE,
	NEGATIVE,
	FXAA
}					t_cfilter;

void				destr(const int cl, t_clr *c);
void				destr2(const int cl, t_clr *c, int *ok);
int					restr(int r, int g, int b);

#endif

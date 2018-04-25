/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ls.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 16:22:11 by alerandy          #+#    #+#             */
/*   Updated: 2018/04/25 17:24:22 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_LS_H
# define MINI_LS_H

# include "rtv1.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/stat.h>
# define _DIRENT struct dirent

void		through_argv(char *argv);
void		mini_ls(void);

#endif

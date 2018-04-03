/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:27:24 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/03 12:27:32 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALS_H
# define GLOBALS_H

void	globals_set(t_globals *globals, char *prop, char *type, void *val);
void	globals_print(t_globals *globals);

#endif

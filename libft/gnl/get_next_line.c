/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 16:07:29 by alerandy          #+#    #+#             */
/*   Updated: 2018/01/16 10:30:46 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		delete_stk(t_list **save)
{
	t_list		*tmp;
	t_stock		*stock;

	stock = (*save)->content;
	if (stock)
	{
		if (stock->str)
			ft_strdel(&(stock->str));
		ft_memdel((void *)&stock);
	}
	stock = NULL;
	tmp = *save;
	*save = (*save)->next;
	ft_memdel((void*)&tmp);
	tmp = NULL;
}

static void		create_line(const int fd, char **line, t_list **save, int end)
{
	t_stock		*stock;
	int			i;
	int			start;

	i = TRUE;
	if (*save)
	{
		stock = (*save)->content;
		if (stock->fd == fd && (stock->done == TRUE || end == 1) && !(*line))
		{
			start = stock->index;
			while (stock->len > stock->index && i == TRUE)
				i = (stock->str[stock->index++] != '\n');
			if (i == FALSE || end == 1)
				*line = ft_strndup(stock->str, stock->index - start - !i);
			else
			{
				stock->done = 0;
				return ;
			}
		}
		else
			create_line(fd, line, &((*save)->next), 0);
		(stock->index == stock->len ? delete_stk(&(*save)) : (stock->done = 0));
	}
}

static int		join_read(const int fd, t_read *red, t_stock **stock, int *eof)
{
	if (red->ret == 0 && !(*stock))
		return ((*eof = TRUE));
	if (!(*stock))
		if (!(*stock = ft_memalloc(sizeof(t_stock))))
			return (-1);
	(*stock)->fd = fd;
	if ((*stock)->str && (*stock)->done == FALSE)
	{
		free(red->buffer);
		if (!(red->buffer = ft_strndup((*stock)->str + (*stock)->index,
						(*stock)->len - (*stock)->index)))
			return (-1);
		(*stock)->index = 0;
		ft_strdel(&((*stock)->str));
	}
	(!red->buffer ? (red->buffer = ft_memalloc(1)) : red->buffer);
	if (!((*stock)->str = ft_strnew(red->ret + (*stock)->len + 1)))
		return (-1);
	(*stock)->str = ft_strcpy((*stock)->str, red->buffer);
	(*stock)->str = ft_strncat((*stock)->str, red->buffed, red->ret);
	(*stock)->len = ft_strlen((*stock)->str);
	ft_strdel(&(red->buffer));
	while (*eof < (*stock)->len)
		(((*stock)->str)[(*eof)++] == '\n' ? ((*stock)->done = TRUE) : *eof);
	return ((*eof = 0));
}

static int		stock_line(const int fd, t_read *red, t_list **save, int *eof)
{
	t_stock		*stock;

	stock = NULL;
	if (!(*save))
	{
		if (join_read(fd, red, &stock, eof) < 0)
			return (-1);
		if (stock)
		{
			*save = ft_lstnew(stock, sizeof(t_stock));
			ft_memdel((void *)&stock);
		}
	}
	else
	{
		stock = (*save)->content;
		if (!stock)
			return (stock_line(fd, red, &((*save)->next), eof));
		if (fd != stock->fd)
			return (stock_line(fd, red, &((*save)->next), eof));
		if (join_read(fd, red, &stock, eof) < 0)
			return (-1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*save = NULL;
	int				eof;
	t_read			red;

	eof = FALSE;
	if (!line || BUFF_SIZE < 1)
		return (-1);
	*line = NULL;
	red.buffer = NULL;
	while (!(*line) && eof == FALSE)
	{
		create_line(fd, line, &save, 0);
		if (!(*line) && eof == FALSE)
		{
			if ((red.ret = read(fd, red.buffed, BUFF_SIZE)) < 0)
				return (-1);
			if (stock_line(fd, &red, &save, &eof) < 0)
				return (-1);
		}
		if (!*line && eof == FALSE)
			(red.ret == 0 ? create_line(fd, line, &save, 1) : (red.ret = 0));
	}
	return (*line != NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_example.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:30:32 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/16 14:31:33 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

void	*input_listener(void *condition)
{
	while (1)
	{
		printf("A key was pressed.\n");
		if (*(int*)condition)
			break ;
		sleep(2);
	}
	pthread_exit(0);
}

int		main(void)
{
	pthread_t	thread;
	int			val;
	int			i;

	val = 0;
	printf("Start\n");
	pthread_create(&thread, NULL, input_listener, &val);
	i = 10;
	while (i)
	{
		getchar();
		i--;
	}
	lock = 1;
	pthread_join(thread, NULL);
	return (0);
}

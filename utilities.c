/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:28:08 by sokur             #+#    #+#             */
/*   Updated: 2023/11/04 17:41:17 by sokur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	remastered_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print(t_philo *philo, char *status)
{
	printf("%ld %d %s\n",
		get_time() - philo->table->dinner_time, philo->phid, status);
}

int	shovel(t_table *table)
{
	pthread_mutex_lock(&table->eyes_on_the_table);
	if (table->dead_philo)
	{
		pthread_mutex_unlock(&table->eyes_on_the_table);
		return (1);
	}
	else
		pthread_mutex_unlock(&table->eyes_on_the_table);
	return (0);
}

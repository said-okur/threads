/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:28:08 by sokur             #+#    #+#             */
/*   Updated: 2023/09/29 11:22:23 by sokur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	// mikrosec : 1 sec = 1.000.000 microsec
	// milisec : 1 sec = 1.000 miliseconds // time.tv_sec = seconds, time.tv_usec = microseconds
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print(t_philo *philo, char *situation)
{
	if (philo->is_dead)
	{
		pthread_mutex_lock(&philo->table->write);
		printf("%ld %d %s\n", get_time() - philo->table->start, philo->phid, situation);
		pthread_mutex_unlock(&philo->table->write);
	}
	else
	{
		pthread_mutex_lock(&philo->table->write);
		printf("%ld %d %s\n", get_time() - philo->table->start, philo->phid, situation);
		pthread_mutex_unlock(&philo->table->write);
	}
}

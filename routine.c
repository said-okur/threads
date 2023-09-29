/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:52:00 by sokur             #+#    #+#             */
/*   Updated: 2023/09/29 20:44:00 by sokur            ###   ########.fr       */
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

void	clear_the_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	print(philo, FORK);
	pthread_mutex_lock(&philo->table->status);
	print(philo, EATING);
	remastered_usleep(philo->table->tteat);
	philo->last_eat = get_time();
	philo->must_eat++;
	pthread_mutex_unlock(&philo->table->status);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print(philo, SLEEPING);
	pthread_mutex_lock(&philo->table->status);
	remastered_usleep(philo->table->ttsleep);
	pthread_mutex_unlock(&philo->table->status);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->status);
	print(philo, THINKING);
	pthread_mutex_unlock(&philo->table->status);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if(philo->phid % 2)
		remastered_usleep(10);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		dead_bodies(philo->table);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thats_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:52:00 by sokur             #+#    #+#             */
/*   Updated: 2023/11/06 13:17:12 by sokur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo)
{
	pthread_mutex_lock((philo->left_fork));
	if (shovel(philo->table))
		return ;
	print(philo, FORK);
	if (philo->table->philo_num == 1)
		return ;
	pthread_mutex_lock((philo->right_fork));
	if (shovel(philo->table))
		return ;
	print(philo, FORK);
	print(philo, EAT);
	remastered_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->die);
	philo->last_bite = get_time();
	philo->bites++;
	pthread_mutex_unlock(&philo->table->die);
	pthread_mutex_unlock((philo->left_fork));
	pthread_mutex_unlock((philo->right_fork));
	if (shovel(philo->table))
		return ;
	print(philo, SLEEP);
	remastered_usleep(philo->table->time_to_sleep);
	if (shovel(philo->table))
		return ;
	print(philo, THINK);
}

void	*gluttony(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (!(philo->phid % 2))
		remastered_usleep(5);
	pthread_mutex_lock(&philo->table->eyes_on_the_table);
	while (!philo->table->dead_philo)
	{
		pthread_mutex_unlock(&philo->table->eyes_on_the_table);
		routine(philo);
		if (philo->table->philo_num == 1)
			return (NULL);
		if (philo->bites == philo->must_eat)
		{
			pthread_mutex_lock(&philo->table->die);
			philo->table->full_stomach++;
			pthread_mutex_unlock(&philo->table->die);
			return (NULL);
		}
		pthread_mutex_lock(&philo->table->eyes_on_the_table);
	}
	pthread_mutex_unlock(&philo->table->eyes_on_the_table);
	return (NULL);
}

void	grave_digger(t_table *table)
{
	int	i;

	while (!table->dead_philo)
	{
		i = -1;
		while (!table->dead_philo && ++i < table->philo_num)
		{
			pthread_mutex_lock(&table->die);
			if (get_time() - table->philos[i].last_bite >= table->time_to_die
				&& table->philos[i].bites != table->must_eat)
			{
				pthread_mutex_lock(&table->eyes_on_the_table);
				table->dead_philo = i + 1;
				pthread_mutex_unlock(&table->eyes_on_the_table);
				print(&table->philos[i], DIE);
			}
			pthread_mutex_unlock(&table->die);
		}
		pthread_mutex_lock(&table->die);
		if (table->full_stomach == table->philo_num)
			return ((void)pthread_mutex_unlock(&table->die));
		pthread_mutex_unlock(&table->die);
		usleep(100);
	}
}

int	enjoy_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_join(table->philos[i].phread, NULL))
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_the_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:42:52 by sokur             #+#    #+#             */
/*   Updated: 2023/09/29 20:43:29 by sokur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void dead_bodies(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < table->philo_num)
	{
		if (table->philos[i].must_eat != -1)
			j++;
		i++;
	}
	i = 0;
	while (i < table->philo_num)
	{
		if (table->philos[i].must_eat == -1)
			i++;
		if (table->philos[i].must_eat == j)
		{
			pthread_mutex_lock(&table->status);
			print(&table->philos[i], DIED);
			pthread_mutex_unlock(&table->status);
			i++;
		}
	}
}

void	to_existence(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_create(&table->philos[i].phread, NULL, routine, &table->philos[i]);
		i++;
	}
	i = 0;
	while(i < table->philo_num)
	{
		pthread_join(table->philos[i].phread, NULL);
		i++;
	}
	pthread_mutex_init(&table->status, NULL);
	pthread_mutex_init(&table->write, NULL);
}

void	init_table(t_table *table)
{
	int	i;

	i = 0;
	table->start = get_time();
	while (i < table->philo_num)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < table->philo_num)
	{
		table->philos[i].phid = i + 1;
		table->philos[i].table = table;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->philo_num];
		table->philos[i].must_eat = table->must_eat;
		table->philos[i].last_eat = get_time();
		table->philos[i].pttdie = table->philos[i].last_eat + table->ttdie;
		i++;
	}
	to_existence(table);
}

int	set_the_table(char **input, t_table *table)
{
	table->philo_num = ft_atoi(input[1]);
	table->ttdie = ft_atoi(input[2]);
	table->tteat = ft_atoi(input[3]);
	table->ttsleep = ft_atoi(input[4]);
	if (input[5])
		table->must_eat = ft_atoi(input[5]);
	else
		table->must_eat = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
		return (0);
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!table->philos)
		return (0);
	init_table(table);
	return (1);
}

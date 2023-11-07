/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:42:52 by sokur             #+#    #+#             */
/*   Updated: 2023/11/04 17:35:28 by sokur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_the_table(char **argv, t_table *table)
{
	table->philo_num = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1837837;
	table->dead_philo = 0;
	table->full_stomach = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!table->forks || !table->philos)
	{
		if (table->forks)
			free(table->forks);
		if (table->philos)
			free(table->philos);
		return (1);
	}
	return (0);
}

int	existence(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		table->philos[i].phid = i + 1;
		table->philos[i].bites = 0;
		table->philos[i].must_eat = table->must_eat;
		table->philos[i].table = table;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->philo_num];
		i++;
	}
	put_mutex(table);
	return (0);
}

int	put_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->eyes_on_the_table, NULL);
	pthread_mutex_init(&table->die, NULL);
	return (0);
}

int	dinner_time(t_table *table)
{
	int	i;

	i = 0;
	table->dinner_time = get_time();
	while (i < table->philo_num)
	{
		table->philos[i].last_bite = get_time();
		pthread_create(
			&(table->philos[i].phread), NULL, gluttony, &table->philos[i]);
		i++;
	}
	return (0);
}

int	clear_the_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->eyes_on_the_table);
	pthread_mutex_destroy(&table->die);
	free(table->forks);
	free(table->philos);
	return (0);
}

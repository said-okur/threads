/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:59:34 by sokur             #+#    #+#             */
/*   Updated: 2023/09/29 20:51:17 by sokur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"


typedef struct s_philo
{
	struct s_table	*table;

	int			phid;
	int			ptteat;
	int			pttsleep;
	long		pttdie;
	int			must_eat;
	int			last_breath;
	long		limit;
	int			is_dead;

	unsigned long	last_eat;

	pthread_t		phread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}t_philo;

typedef struct s_table
{
	int				philo_num;
	unsigned long	ttdie;
	unsigned long	tteat;
	unsigned long	ttsleep;
	int				must_eat;
	unsigned long	start;
	int				is_dead;
	
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	status;
	pthread_mutex_t write;
	pthread_mutex_t body;
}t_table;

int			check_inputs(int argc, char **argv);
int			ft_atoi(const char *str);
unsigned long		get_time(void);
void		print(t_philo *philo, char *situation);

int		set_the_table(char **input, t_table *table);
void	*routine(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	clear_the_table(t_table *table);
void dead_bodies(t_table *table);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:59:34 by sokur             #+#    #+#             */
/*   Updated: 2023/11/04 17:40:31 by sokur            ###   ########.fr       */
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
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIE "died"

//philosophers
typedef struct s_philo
{
	int				phid;
	long			last_bite;
	int				bites;
	int				must_eat;

	struct s_table	*table;
	pthread_t		phread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

}	t_philo;

//table
typedef struct s_table
{
	long			dinner_time;
	int				philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;

	int				dead_philo;
	int				full_stomach;

	pthread_mutex_t	eyes_on_the_table;
	pthread_mutex_t	die;

	t_philo			*philos;
	pthread_mutex_t	*forks;
}t_table;

//utils
void	print(t_philo *philo, char *status);
void	remastered_usleep(unsigned long time);
int		check_inputs(int argc, char **argv);
int		ft_atoi(const char *str);
long	get_time(void);

int		set_the_table(char **input, t_table *table);
void	grave_digger(t_table *table);
int		enjoy_dinner(t_table *table);
int		dinner_time(t_table *table);
int		put_mutex(t_table *table);
int		existence(t_table *table);
int		clear_the_table(t_table *table);
void	*gluttony(void *param);
int		shovel(t_table *table);

#endif

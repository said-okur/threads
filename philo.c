/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:36:42 by sokur             #+#    #+#             */
/*   Updated: 2023/09/29 20:49:22 by sokur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ----------------------- Wrong input! -------------------------\n
// --------- 'at least 4 arguments, at most 5 arguments' ---------

// Arg 1 : number_of_philosophers ~~~~~~~~~~~~~~~~~~~~~~~ (1 - 200)
// Arg 2 : time_to_die --------------------------- (higher than 60)
// Arg 3 : time_to_eat ~~~~~~~~~~~~~~~~~~~~~~~~~~~ (higher than 60)
// Arg 4 : time_to_sleep ------------------------- (higher than 60)
// Arg 5 (optional) : num_each_philosopher_must_eat (higher than 0)



int	main(int argc, char **argv) // 5 800 200 200 7
{
	t_table	table;

	check_inputs(argc, argv);
	set_the_table(argv, &table);
	while(1)// die controller
	{
		pthread_mutex_lock(&table.status);
		if (table.is_dead)
		{
			pthread_mutex_unlock(&table.status);
			clear_the_table(&table);
			break;
		}
		pthread_mutex_unlock(&table.status);
	}
	return (0);
}

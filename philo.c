/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:36:42 by sokur             #+#    #+#             */
/*   Updated: 2023/11/04 17:32:02 by sokur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_inputs(argc, argv))
		return (1);
	set_the_table(argv, &table);
	existence(&table);
	dinner_time(&table);
	grave_digger(&table);
	enjoy_dinner(&table);
	clear_the_table(&table);
	return (1);
}

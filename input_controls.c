/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:53:22 by sokur             #+#    #+#             */
/*   Updated: 2023/09/27 16:29:08 by sokur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		res;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (sign * res);
}

static int	is_digit(int argc, char **argv)
{
	int	i;
	int	k;

	i = 1;
	while (i < argc)
	{
		k = 0;
		while (argv[i][k] != '\0')
		{
			if (argv[i][k] < '0' || argv[i][k] > '9')
				return (1);
			k++;
		}
		i++;
	}
	return (0);
}

static int	value_control(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 1)
			return (1);
		i++;
	}
	if (ft_atoi(argv[1]) > 200)
		return (1);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (1);
	return (0);
}

static void put_instructions()
{
	printf("\n\n");
	printf("----------------------- Wrong input! -------------------------\n\n");
	printf("--------- 'at least 4 arguments, at most 5 arguments' --------- \n");
	printf("\n");
	printf("Arg 1 : number_of_philosophers ~~~~~~~~~~~~~~~~~~~~~~~ (1 - 200)\n");
	printf("Arg 2 : time_to_die --------------------------- (higher than 60)\n");
	printf("Arg 3 : time_to_eat ~~~~~~~~~~~~~~~~~~~~~~~~~~~ (higher than 60)\n");
	printf("Arg 4 : time_to_sleep ------------------------- (higher than 60)\n");
	printf("Arg 5 (optional) : num_each_philosopher_must_eat (higher than 0)\n");
	printf("\n");
	printf("---------------------------------------------------------------\n\n");
}

int check_inputs(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		put_instructions();
		exit(0);
	}
	if (is_digit(argc, argv) || value_control(argc, argv))
	{
		put_instructions();
		exit(0);
	}
	return (0);
}

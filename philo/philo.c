/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:50:02 by rgiambon          #+#    #+#             */
/*   Updated: 2024/10/14 13:25:28 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(char **argv)
{
	printf("[0] 1 is thinking\n");
	usleep(my_atol(argv[2]) * 1000);
	printf("[%lu] 1 is dead\n", my_atol(argv[2]));
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;

	philo = NULL;
	data = NULL;
	if (!arg_check(argc, argv))
		return (0);
	if (my_atol(argv[1]) == 1)
	{
		one_philo(argv);
		return (0);
	}
	init_values(argc, argv, &philo, &data);
	if (!init_mutex(data, philo))
		return (0);
	if (!make_threads(philo, data))
		return (0);
	int i = 0;
	while (i < data->philo_num)
	{
		printf("[%d] meals eaten: [%d]\n", i, philo[i].meals_eaten);
		i++;
	}
//	destroy_all(&data);
	return (0);
}

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

int	edge_case(int argc, char **argv)
{
	if (my_atol(argv[1]) == 1)
	{
		printf("[0] 1 is thinking\n");
		usleep(my_atol(argv[2]) * 1000);
		printf("[%lu] 1 is dead\n", my_atol(argv[2]));
		return (1);
	}
	if (argc == 6)
	{
		if (my_atol(argv[5]) == 0)
		{
			printf("Every philo had 0 meals.\n");
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;

	philo = NULL;
	data = NULL;
	if (!arg_check(argc, argv))
		return (0);
	if (edge_case(argc, argv))
		return (0);
	if(!init_data(argc, argv, &data))
		return (0);
	if(!init_philo(&philo, &data))
		return (0);
	if (!init_mutex(data, philo))
	{
		free_memory(data, philo);
		return (0);
	}
	make_threads(philo, data);
	destroy_mutex(data, philo);
	free_memory(data, philo);
	return (0);
}

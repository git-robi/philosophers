/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:42:25 by rgiambon          #+#    #+#             */
/*   Updated: 2024/10/16 11:42:19 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_current_time(void)
{
	struct timeval		tmp;
	unsigned int		current_time;

	gettimeofday(&tmp, NULL);
	current_time = (unsigned int)tmp.tv_sec * 1000 + tmp.tv_usec * 0.001;
	return (current_time);
}

unsigned int	get_sim_time(t_data *data)
{
	return (get_current_time() - data->start);
}

void	init_values(int	argc, char **argv, t_philo **philo, t_data **data)
{
	int	i;
	
	*data = malloc(sizeof(t_data) * 1);
// add check
	(*data)->philo_num = (int)my_atol(argv[1]);
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->philo_num);
// add check
	(*data)->time_to_die = (int)my_atol(argv[2]);
	(*data)->time_to_eat = (int)my_atol(argv[3]);
	(*data)->time_to_sleep = (int)my_atol(argv[4]);
	printf("%lu, %d, %d\n", (*data)->time_to_die, (*data)->time_to_eat, (*data)->time_to_sleep);
	if (argc == 6)
		(*data)->n_meals = (int)my_atol(argv[5]);
	else
		(*data)->n_meals = -1;
	(*data)->is_over = 0;
	(*data)->all_are_done = 0;
	(*data)->start = get_current_time();
	*philo = malloc(sizeof(t_philo) * (*data)->philo_num);
// add check
	i = 0;
	while (i < (*data)->philo_num)
	{
		(*philo)[i].last_meal = 0;
		(*philo)[i].idx = i;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].data = *data;
		i++;
	}
	
}

int	make_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
//	printf("philo_num: %d\n", data->philo_num);
	while (i < data->philo_num)
	{
		if (pthread_create(&philo[i].th, NULL, routine, &philo[i]) != 0)
			return (0);
		i++;
	}
	monitor(philo, data);
	i = 0;
//	printf("philo num in make threads: %d\n", data->philo_num); 
	while (i < data->philo_num)
	{
//		printf("enter join\n");
		if (pthread_join(philo[i].th, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_mutex(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->is_dead, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->printer, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->are_done, NULL) != 0)
                return (0);
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&philo[i].meal, NULL) != 0)
			return(0);
		philo[i].left_fork = &data->forks[i];
		printf("philo [%d] left fork: %p\n", i, philo[i].left_fork);
		philo[i].right_fork = &data->forks[(i + 1) % data->philo_num];
		printf("philo [%d] right fork: %p\n", i, philo[i].right_fork);
		i++;
	}
	return (1);
}

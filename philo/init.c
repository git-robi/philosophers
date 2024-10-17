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

int	init_data(int argc, char **argv, t_data **data)
{
	*data = malloc(sizeof(t_data) * 1);
	if (*data == NULL)
		return (0);
	(*data)->philo_num = (int)my_atol(argv[1]);
	(*data)->forks = NULL;
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->philo_num);
	if ((*data)->forks == NULL)
	{
		free(*data);
		return (0);
	}
	(*data)->time_to_die = (int)my_atol(argv[2]);
	(*data)->time_to_eat = (int)my_atol(argv[3]);
	(*data)->time_to_sleep = (int)my_atol(argv[4]);
	if (argc == 6)
		(*data)->n_meals = (int)my_atol(argv[5]);
	else
		(*data)->n_meals = -1;
	(*data)->is_over = 0;
	(*data)->all_are_done = 0;
	(*data)->start = get_current_time();
	return (1);
}

int	init_philo(t_philo **philo, t_data **data)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * (*data)->philo_num);
	if (*philo == NULL)
	{	
		free_memory(*data, *philo);
                return (0);
	}
        i = 0;
        while (i < (*data)->philo_num)
        {
                (*philo)[i].last_meal = 0;
                (*philo)[i].idx = i;
                (*philo)[i].meals_eaten = 0;
                (*philo)[i].data = *data;
                i++;
	}
	return (1);
}

void	make_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&philo[i].th, NULL, routine, &philo[i]) != 0)
		{
			pthread_mutex_lock(&data->is_dead);
			data->is_over = 1;
			pthread_mutex_lock(&data->is_dead);
			return ;
		}
		i++;
	}
	monitor(philo, data);
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(philo[i].th, NULL) != 0)
			return ;
		i++;
	}
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
		philo[i].right_fork = &data->forks[(i + 1) % data->philo_num];
		i++;
	}
	return (1);
}

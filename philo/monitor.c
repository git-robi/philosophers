/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:45:27 by rgiambon          #+#    #+#             */
/*   Updated: 2024/10/16 11:39:35 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_philo *philo, t_data *data)
{
	int	i;

	while (!data->is_over && !all_are_done(philo))
	{
		i = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_lock(&philo[i].meal);
			if (get_sim_time(data) - philo[i].last_meal > data->time_to_die)
			{
				pthread_mutex_lock(&data->is_dead);
				data->is_over = 1;
				pthread_mutex_unlock(&data->is_dead);
				pthread_mutex_lock(&data->printer);
				printf("%u %d is dead.\n", get_sim_time(data), philo[i].idx);
				pthread_mutex_unlock(&data->printer);
				return ;
			}
			pthread_mutex_unlock(&philo[i].meal);
			i++;
		}
	}
}

long	get_time_diff(struct timeval *start)
{
	struct timeval	curr_time;
	long			milliseconds;
	long			sec_diff;
	long			microsec_diff;

	gettimeofday(&curr_time, NULL);
	sec_diff = curr_time.tv_sec - start->tv_sec;
	microsec_diff = curr_time.tv_usec - start->tv_usec;
	milliseconds = (sec_diff * 1000) + (microsec_diff / 1000);
	return (milliseconds);
}

int	all_are_done(t_philo *philo)
{
	int	i;

	i = 0;
//	printf("n_meals = %d\n", philo[i].data->n_meals);
	if (philo[i].data->n_meals > 0)
	{
		while (i < philo[i].data->philo_num)
		{
			if (philo[i].meals_eaten < philo[i].data->n_meals)
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

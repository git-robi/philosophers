/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:46:09 by rgiambon          #+#    #+#             */
/*   Updated: 2024/10/13 15:46:12 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_memory(t_data *data, t_philo *philo)
{
	if (data->forks != NULL)
		free(data->forks);
	if (data != NULL)
		free(data);
	if (philo != NULL)
		free(philo);
}

void	destroy_mutex(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(philo[i].right_fork);
		pthread_mutex_destroy(philo[i].left_fork);
		pthread_mutex_destroy(&philo[i].meal);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->printer);
	pthread_mutex_destroy(&data->are_done);
	pthread_mutex_destroy(&data->is_dead);
}

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

long	my_atol(const char *str)
{
	int			i;
	long	result;
	int			sign;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:37:54 by rgiambon          #+#    #+#             */
/*   Updated: 2024/10/19 15:40:17 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	printer(char *s, t_philo *philo, char *color)
{
	pthread_mutex_lock(&philo->data->printer);
	pthread_mutex_lock(&philo->data->is_dead);
	pthread_mutex_lock(&philo->data->are_done);
	if (philo->data->is_over || philo->data->all_are_done)
	{
		pthread_mutex_unlock(&philo->data->printer);
		pthread_mutex_unlock(&philo->data->is_dead);
		pthread_mutex_unlock(&philo->data->are_done);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->is_dead);
	pthread_mutex_unlock(&philo->data->are_done);
	printf("[%u] %d %s %s %s\n", get_sim_time(philo->data), philo->idx + 1, color, s, RESET);
	pthread_mutex_unlock(&philo->data->printer);
	return (0);
}

int	philo_eats(t_philo *philo)
{
	if (printer("is eating", philo, GREEN) != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = get_sim_time(philo->data);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->meal);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (printer("has taken right fork", philo, YELLOW) != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	if (philo->data->philo_num == 1)
	{
		usleep(philo->data->time_to_die + 1 * 1000);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(philo->left_fork);
	if (printer("has taken left fork", philo, YELLOW) != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->idx % 2 != 0)
		usleep(1000);
	while (1)
	{
		if (printer("is thinking", philo, BLUE) != 0)
			break ;
		if (pick_up_forks(philo) == 0)
		{
			if (philo_eats(philo) != 0)
				break ;
		}
		else
			break ;
		if (printer("is sleeping", philo, CYAN) != 0)
			break ;
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}

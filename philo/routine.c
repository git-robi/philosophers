#include "philo.h"

int	printer(char *s, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->printer);
	pthread_mutex_lock(&philo->data->is_dead);
	pthread_mutex_lock(&philo->data->are_done);
	if (philo->data->is_over || philo->data->all_are_done)
	{
		pthread_mutex_unlock(&philo->data->are_done);
		pthread_mutex_unlock(&philo->data->is_dead);
		pthread_mutex_unlock(&philo->data->printer);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->are_done);
	pthread_mutex_unlock(&philo->data->is_dead);
	printf("[%u] %d %s\n", get_sim_time(philo->data), philo->idx + 1, s);
	pthread_mutex_unlock(&philo->data->printer);
	return (0);
}

int	philo_eats(t_philo *philo)
{
	if (printer("is eating", philo) != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = get_sim_time(philo->data);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->meal);
//	if (eat_and_sleep(philo, philo->data->time_to_eat) != 0)
//	{
//		pthread_mutex_unlock(philo->left_fork);
//		pthread_mutex_unlock(philo->right_fork);
//		return (1);
//	}
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return(0);
}
	
int	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (printer("has taken right fork", philo) != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(philo->left_fork);
	if (printer("has taken left fork", philo) != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}
	
void	*routine(void  *arg)
{
	t_philo *philo; 

	philo = (t_philo *)arg;
	if (philo->idx % 2 != 0)
		usleep(1000);
	while (1)
	{
		if (printer("is thinking", philo) != 0)
			break ;
		if (pick_up_forks(philo) == 0)
		{
			if (philo_eats(philo) != 0)
				break;
		}
		else
			break ;
		if (printer("is sleeping", philo) != 0)
			break ;
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}

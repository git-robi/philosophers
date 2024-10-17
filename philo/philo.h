/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:50:13 by rgiambon          #+#    #+#             */
/*   Updated: 2024/10/16 11:39:10 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct	s_data t_data;

typedef struct s_data
{
	pthread_mutex_t	is_dead;
	pthread_mutex_t are_done;
	pthread_mutex_t	printer;
	pthread_mutex_t	*forks;
	int				is_over;
	int				all_are_done;
	int				philo_num;
	unsigned long	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	unsigned long	start;
}	t_data;

typedef struct s_philo
{
	t_data		*data;
	pthread_t		th;
	pthread_mutex_t	meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				idx;
	unsigned long		last_meal;
	int		meals_eaten;
}	t_philo;
	
//checks
int		arg_check(int argc, char **argv);
int limit_check(int argc, char **argv);
//init
int     init_philo(t_philo **philo, t_data **data);
int     init_data(int argc, char **argv, t_data **data);
void make_threads(t_philo *philo, t_data *data);
int init_mutex(t_data *data, t_philo *philo);
//routine
void	*routine(void *arg);
int eat_and_sleep(t_philo *philo, int time_to);
int pick_up_forks(t_philo *philo);
int philo_eats(t_philo *philo);
int printer(char *s, t_philo *philo);
//monitor
void    monitor(t_philo *philo, t_data *data);
long    get_time_diff(struct timeval *start);
void all_are_done(t_philo *philo, t_data *data);
//utils
long    my_atol(const char *str);
void    free_memory(t_data *data, t_philo *philo);
void    destroy_mutex(t_data *data, t_philo *philo);
unsigned int	get_current_time(void);
unsigned int	get_sim_time(t_data *data);
#endif

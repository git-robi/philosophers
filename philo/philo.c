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

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;

	philo = NULL;
	data = NULL;
	if (!arg_check(argc, argv))
		return (0);
	printf("1\n");
	init_values(argc, argv, &philo, &data);
	printf("2\n");
	if (!init_mutex(data, philo))
		return (0);
	printf("3\n");
	if (!make_threads(philo, data))
		return (0);
	printf("4\n");
//	destroy_all(&data);
	return (0);
}

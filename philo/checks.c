/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:41:24 by rgiambon          #+#    #+#             */
/*   Updated: 2024/10/14 13:27:14 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"	

int	limit_check(int argc, char **argv)
{
	int	i;
	
	if (my_atol(argv[1]) > INT_MAX || my_atol(argv[1]) <= 0)
		return (0);
	i = 2;
	while (i < argc)
	{
		if (my_atol(argv[i]) > INT_MAX || my_atol(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

int	arg_check(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	if (!limit_check(argc, argv))
		return (0);
	return (1);
}


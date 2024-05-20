/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/20 12:59:57 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_error(char *error_massege)
{
	int len;

	len = 0;
	while (error_massege[len])
		len++;
	write(STDERR, error_massege, len);
}

int check_stop(t_data *data)
{
	pthread_mutex_lock(&data->lock_n_times);
	if (data->stop == 0)
	{
		pthread_mutex_unlock(&data->lock_n_times);
		return (-1);
	}
	pthread_mutex_unlock(&data->lock_n_times);
	return (GOOD);
}

void clean_all(t_data *data)
{
	int i;

	i = 0;
	while (i < data->total_ph)
	{
		pthread_mutex_destroy(data->forks[i]);
		free(data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->lock_n_times);
	free(data->forks);
	free(data->philos);
}

void leaks(void)
{
	system("leaks philo");
}

int main(int ac, char **av)
{
	t_data data;

	// atexit(leaks);
	if (ac < 5 || ac > 6)
	{
		ft_error("Error: incorrect number of arguments\n");
		return (1);
	}
	if (set_init(&data, ac, av) == ERROR)
		return (1);
	if (add_threads(&data) == ERROR)
	{
		clean_all(&data);
		return (1);
	}
	clean_all(&data);
}

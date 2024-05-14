/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:10:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/14 14:39:11 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int set_default(t_data *data, int ac, char **av)
{
	data->total_ph = convert_int(av[1]);
	if (data->total_ph == ERROR)
		return (ERROR);
	data->t_die = convert_int(av[2]);
	if (data->t_die == ERROR)
		return (ERROR);
	data->t_eat = convert_int(av[3]);
	if (data->t_eat == ERROR)
		return (ERROR);
	data->t_sleep = convert_int(av[4]);
	if (data->t_sleep == ERROR)
		return (1);
	if (ac == 6)
	{
		data->n_t_m_eat = convert_int(av[5]);
		if (data->n_t_m_eat == ERROR)
			return (ERROR);
	}
	else
		data->n_t_m_eat = 0;
	data->dead = LIFE;
	return (GOOD);
}

int data_alloc(t_data *data)
{
	int i;

	i = 0;
	data->forks = malloc(data->total_ph * sizeof(pthread_mutex_t *));
	if (data->forks == NULL)
		return (ERROR);
	while (i < data->total_ph)
	{
		data->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (data->forks[i] == NULL)
			return (ERROR);
		i++;
	}
	data->philos = malloc(data->total_ph * sizeof(t_philo));
	if (data->philos == NULL)
		return (ERROR);
	return (GOOD);
}

int set_id_forks(t_data *data)
{
	int id;

	id = 0;
	if (pthread_mutex_init(&data->lock, NULL))
			return (ERROR);
	while (id < data->total_ph)
	{
		data->philos[id].id = id + 1;
		data->philos[id].is_eating = NOT_EATING;
		data->philos[id].last_meal = get_time();
		if (pthread_mutex_init(&(data->philos[id].write), NULL))
			return (ERROR);
		if (pthread_mutex_init((data->forks)[id], NULL))
			return (ERROR);
		id++;
	}
	return (GOOD);
}

void gave_forks(t_data *data)
{
	int i;

	i = 0;
	while (i < data->total_ph - 1)
	{
		(data->philos[i]).r_fork = data->forks[i];
		(data->philos[i]).data = data;
		(data->philos[i]).l_fork = data->forks[i + 1];
		i++;
	}
	(data->philos[i]).r_fork = data->forks[i];
	(data->philos[i]).data = data;
	(data->philos[i]).l_fork = data->forks[0];
}

int set_init(t_data *data, int ac, char **av)
{
	if (set_default(data, ac, av) == ERROR)
	{
		ft_error("Error: Incorrect number\n");
		return (ERROR);
	}
	if (data_alloc(data) == ERROR)
	{
		ft_error("Error: Allocation failed\n");
		return (ERROR);
	}
	if (set_id_forks(data)== ERROR)
	{
		ft_error("Error: pthread_mutex_init crashed\n");
		return (ERROR);
	}
	gave_forks(data);
	return (GOOD);
}

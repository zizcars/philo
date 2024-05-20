/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:10:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/20 15:43:28 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_numbers(t_data *data, int ac, char **av)
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
		return (ERROR);
	if (ac == 6)
	{
		data->n_t_m_eat = convert_int(av[5]);
		if (data->n_t_m_eat == ERROR)
			return (ERROR);
	}
	else
		data->n_t_m_eat = 0;
	data->dead = LIFE;
	data->stop = 1;
	return (GOOD);
}

static int	data_alloc(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->total_ph * sizeof(pthread_mutex_t *));
	if (data->forks == NULL)
		return (ERROR);
	data->philos = malloc(data->total_ph * sizeof(t_philo));
	if (data->philos == NULL)
		return (ERROR);
	while (i < data->total_ph)
	{
		data->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (data->forks[i] == NULL)
			return (ERROR);
		if (i % 2 == 0)
			data->philos[i].state = go_eat;
		else
			data->philos[i].state = go_sleep;
		i++;
	}
	return (GOOD);
}

static int	set_philo_info(t_data *data)
{
	int	id;

	id = 0;
	while (id < data->total_ph)
	{
		data->philos[id].id = id + 1;
		if (data->n_t_m_eat == 0)
			data->philos[id].n_times = -1;
		else
			data->philos[id].n_times = data->n_t_m_eat;
		data->philos[id].last_meal = get_time();
		if (pthread_mutex_init(&(data->philos[id].meal_mtx), NULL))
			return (ERROR);
		if (pthread_mutex_init(&(data->philos[id].n_times_mtx), NULL))
			return (ERROR);
		if (pthread_mutex_init((data->forks)[id], NULL))
			return (ERROR);
		id++;
	}
	return (GOOD);
}

static int	gave_forks(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->lock, NULL))
		return (ERROR);
	if (pthread_mutex_init(&data->lock_n_times, NULL))
		return (ERROR);
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
	return (GOOD);
}

int	set_init(t_data *data, int ac, char **av)
{
	if (set_numbers(data, ac, av) == ERROR)
	{
		ft_error("Error: Incorrect number\n");
		return (ERROR);
	}
	if (data_alloc(data) == ERROR)
	{
		ft_error("Error: Allocation failed\n");
		return (ERROR);
	}
	if (set_philo_info(data) == ERROR || gave_forks(data) == ERROR)
	{
		ft_error("Error: pthread_mutex_init crashed\n");
		return (ERROR);
	}
	return (GOOD);
}

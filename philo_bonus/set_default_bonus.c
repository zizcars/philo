/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:10:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/22 16:09:40 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		return (ERROR);
	if (ac == 6)
	{
		data->n_t_m_eat = convert_int(av[5]);
		if (data->n_t_m_eat == ERROR)
			return (ERROR);
	}
	else
		data->n_t_m_eat = 0;
	if (data->n_t_m_eat == 0)
		data->n_times = -1;
	else
		data->n_times = data->n_t_m_eat;
	data->dead = LIFE;
	return (GOOD);
}

int data_alloc(t_data *data)
{
	int i;

	i = 0;
	data->philos = malloc(data->total_ph * sizeof(t_philo));
	if (data->philos == NULL)
		return (ERROR);
	return (GOOD);
}

int set_id_forks(t_data *data)
{
	int id;

	id = 0;
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->total_ph);
	if (data->forks == SEM_FAILED)
	{
		ft_error("Can't create semaphone with name forks\n");
		return (ERROR);
	}
	sem_unlink("lock");
	data->lock = sem_open("lock", O_CREAT | O_EXCL, 0644, 1);
	if (data->lock == SEM_FAILED)
	{
		ft_error("Can't create semaphone with name lock\n");
		return (ERROR);
	}
	sem_unlink("print");
	data->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print == SEM_FAILED)
	{
		ft_error("Can't create semaphone with name print\n");
		return (ERROR);
	}
	sem_unlink("sem_fast");
	data->sem_fast = sem_open("sem_fast", O_CREAT | O_EXCL, 0644, 1);
	if (data->sem_fast == SEM_FAILED)
	{
		ft_error("Can't create semaphone with name sem_fast\n");
		return (ERROR);
	}
	sem_unlink("sem_start");
	data->sem_start = sem_open("sem_start", O_CREAT | O_EXCL, 0644, 0);
	if (data->sem_start == SEM_FAILED)
		exit(ERROR);
	while (id < data->total_ph)
	{
		data->philos[id].id = id + 1;
		data->philos[id].data = data;
		if (id % 2 == 0)
			data->philos[id].state = go_eat;
		else
			data->philos[id].state = go_sleep;
		if (data->n_t_m_eat)
			data->philos[id].n_times_eat = data->n_t_m_eat;
		else
			data->philos[id].n_times_eat = -1;
		id++;
	}
	return (GOOD);
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
	if (set_id_forks(data) == ERROR)
	{
		return (ERROR);
	}
	return (GOOD);
}

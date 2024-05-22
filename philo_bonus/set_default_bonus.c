/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:10:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/22 19:26:57 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void set_numbers(t_data *data, int ac, char **av)
{
	data->total_ph = convert_int(av[1]);
	data->t_die = convert_int(av[2]);
	data->t_eat = convert_int(av[3]);
	data->t_sleep = convert_int(av[4]);
	if (ac == 6)
	{
		data->n_t_m_eat = convert_int(av[5]);
		data->n_times = data->n_t_m_eat;
	}
	else
	{
		data->n_t_m_eat = 0;
		data->n_times = -1;
	}
	data->dead = LIFE;
	data->philos = malloc(data->total_ph * sizeof(t_philo));
	data->pid = malloc(sizeof(pthread_t) * data->total_ph);
	if (data->philos == NULL || data->pid == NULL || data->total_ph > CHILD_MAX)
	{
		ft_error("Error: Allocation failed\n");
		exit(EXIT_FAILURE);
	}
}

void creat_sem(sem_t **sem, char *sem_name, int n)
{
	sem_unlink(sem_name);
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, n);
	if (*sem == SEM_FAILED)
	{
		ft_error("Can't create semaphone\n");
		exit(EXIT_FAILURE);
	}
}

void set_philo_info(t_data *data)
{
	int id;

	id = 0;
	creat_sem(&data->forks, "forks", data->total_ph);
	creat_sem(&data->lock, "lock", 1);
	creat_sem(&data->print, "print", 1);
	creat_sem(&data->sem_fast, "sem_fast", 1);
	creat_sem(&data->sem_start, "sem_start", 0);
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
}

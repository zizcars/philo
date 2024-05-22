/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managment_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/22 19:53:26 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long check_last_meal(t_philo *philo, int update)
{
	long last_meal;

	last_meal = -1;
	sem_wait(philo->sem_last_meal);
	if (update)
		philo->last_meal = get_time();
	else
		last_meal = philo->last_meal;
	sem_post(philo->sem_last_meal);
	return (last_meal);
}

static void philosopher(t_philo *philo)
{
	pthread_t checker;
	int one_time = 1;

	philo->last_meal = -1;
	creat_sem(&philo->sem_last_meal, "sem_last_meal", 1);
	if (philo->data->total_ph > 1)
		pthread_create(&checker, NULL, death_checker, philo);
	while (philo->n_times_eat != 0)
	{
		sem_wait(philo->data->sem_start);
		if (one_time)
		{
			check_last_meal(philo, 1);
			one_time = 0;
		}
		if (philo->state == go_eat)
			eating(philo);
		else
			sleeping(philo);
		sem_post(philo->data->sem_start);
	}
	sem_close(philo->sem_last_meal);
	sem_unlink("sem_last_meal");
	exit(EXIT_SUCCESS);
}

static void wait_clean(t_data *data)
{
	int i;

	while (waitpid(0, NULL, 0) > 0)
	{
		i = 0;
		while (i < data->total_ph)
			kill(data->pid[i++], SIGKILL);
		clean(data);
		exit(EXIT_SUCCESS);
	}
}

void creat_philos(t_data *data)
{
	int id;
	int i_pid;

	id = 0;
	data->start_t = get_time();
	while (id < data->total_ph)
	{
		data->pid[id] = fork();
		if (data->pid[id] == -1)
		{
			i_pid = 0;
			while (i_pid < id)
				kill(data->pid[i_pid++], SIGKILL);
			clean(data);
			exit(EXIT_FAILURE);
		}
		else if (data->pid[id] == 0)
			philosopher(&data->philos[id]);
		id++;
	}
	while (id--)
		sem_post(data->sem_start);
	wait_clean(data);
}



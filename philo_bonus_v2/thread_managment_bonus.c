/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managment_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/16 10:58:31 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long get_time(void)
{
	struct timeval time_now;

	if (gettimeofday(&time_now, NULL))
		return (ERROR);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

void print_message(char *message, t_philo *philo)
{
	// sem_wait(philo->data->lock);
	if (philo->data->dead != DIED)
		printf("%ld %d %s\n", get_time() - philo->start, philo->id, message);
	// sem_post(philo->data->lock);
}

void ft_sleep(int time_ms, t_philo *philo)
{
	long start, end;
	long elapsed;
	(void)philo;
	while (time_ms > 0)
	{
		start = get_time();
		usleep(1000);
		// sem_wait(philo->data->lock);
		// if (philo->data->dead == DIED)
		// {
		// 	// sem_post(philo->data->lock);
		// 	return (DIED);
		// }
		// sem_post(philo->data->lock);
		end = get_time();
		elapsed = end - start;
		time_ms -= elapsed;
	}
	// return (LIFE);
}

void philosopher(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(100);
	philo->start = get_time();
	while (philo->data->dead == LIFE) //(check_death(philo) == LIFE)//(check_n_times(philo->data) == GOOD)
	{
		print_message("is thinking", philo);
		routine(philo);
	}
	exit(GOOD);
}

void add_threads(t_data *data)
{
	int id;
	pid_t *pid;

	pid = malloc(sizeof(pthread_t) * (data->total_ph));
	if (pid == NULL)
		exit(ERROR);
	id = 0;
	while (id < data->total_ph)
	{
		pid[id] = fork();
		if (pid[id] == -1)
		{
			free(pid);
			exit(ERROR);
		}
		else if (pid[id] == 0)
			philosopher(&data->philos[id]);
		id++;
	}
	data->dead = monitor(data);
	int j;
	if (data->dead == DIED)
	{
		j = 0;
		if (data->dead == DIED)
			while (j < data->total_ph)
				kill(pid[j++], SIGKILL);
	}
	waitpid(-1, NULL, 0);
	free(pid);
	exit(ERROR);
	// join_free(data, pid);
}

void join_free(t_data *data, pid_t *pid)
{
	// int status;
	int i;
	int j;

	i = 0;
	while (waitpid(-1, NULL, 0) > 0)
	{
		j = 0;
		if (data->dead == DIED)
			while (j < data->total_ph)
				kill(pid[j++], SIGKILL);
		free(pid);
		exit(ERROR);
	}
}

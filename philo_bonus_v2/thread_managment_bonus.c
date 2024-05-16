/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managment_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/16 12:18:21 by achakkaf         ###   ########.fr       */
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
	printf("%ld %d %s\n", get_time() - philo->start, philo->id, message);
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
		end = get_time();
		elapsed = end - start;
		time_ms -= elapsed;
	}
}

void *death(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_time() - philo->last_meal > philo->data->t_die)
		{
			printf("\e[31m%ld %d is died\n\e[0m", get_time() - philo->last_meal, philo->id);
			exit(DIED);
		}
	}
	return (NULL);
}

void philosopher(t_philo *philo)
{
	pthread_t checker;

	if (philo->id % 2 == 0)
		usleep(100);
	pthread_create(&checker, NULL, death, philo);
	philo->start = get_time();
	while (1)
	{
		print_message("is thinking", philo);
		routine(philo);
	}
}

void *check_eat_times(void *arg)
{
	t_data *data;
	int j;

	data = (t_data *)arg;
	while (data->n_times)
	{
		sem_wait(data->lock);
		data->n_times--;
		sem_post(data->lock);
	}
	j = 0;
	while (j < data->total_ph)
		kill(data->pid[j++], SIGKILL);
	free(data->pid);
	exit(0);
}

void add_threads(t_data *data)
{
	int id;
	int j;
	pthread_t time_eat;

	data->pid = malloc(sizeof(pthread_t) * (data->total_ph));
	if (data->pid == NULL)
		exit(ERROR);
	id = 0;
	while (id < data->total_ph)
	{
		data->pid[id] = fork();
		if (data->pid[id] == -1)
		{
			free(data->pid);
			exit(ERROR);
		}
		else if (data->pid[id] == 0)
			philosopher(&data->philos[id]);
		id++;
	}
	if (data->n_t_m_eat)
	{
		data->n_times = data->n_t_m_eat;
		pthread_create(&time_eat, NULL, check_eat_times, data);
	}
	while (waitpid(0, NULL, 0) > 0)
	{
		j = 0;
		while (j < data->total_ph)
			kill(data->pid[j++], SIGKILL);
		free(data->pid);
		exit(0);
	}
}

// void join_free(t_data *data, pid_t *pid)
// {
// 	// int status;
// 	int i;
// 	int j;

// 	i = 0;
// 	while (waitpid(-1, NULL, 0) > 0)
// 	{
// 		j = 0;
// 		if (data->dead == DIED)
// 			while (j < data->total_ph)
// 				kill(pid[j++], SIGKILL);
// 		free(pid);
// 		exit(ERROR);
// 	}
// }

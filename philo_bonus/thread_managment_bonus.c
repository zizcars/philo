/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managment_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/20 18:01:44 by achakkaf         ###   ########.fr       */
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
	printf("%ld %d %s\n", get_time() - philo->data->start_t, philo->id, message);
}

void mssleep(int time_ms)
{
	long start;

	start = get_time();
	while (get_time() - start < time_ms)
		usleep(100);
}

void *death(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_time() - philo->last_meal >= philo->data->t_die)
		{
			sem_wait(philo->data->lock);
			printf("\e[31m%ld %d is died\n\e[0m", get_time() - philo->data->start_t, philo->id);
			exit(DIED);
		}
	}
	return (NULL);
}

void philosopher(t_philo *philo)
{
	pthread_t checker;

	philo->last_meal = get_time();
	pthread_create(&checker, NULL, death, philo);
	while (1)
	{
		if (philo->state == go_eat)
			eating(philo);
		else
			sleeping(philo);
	}
}

// void *check_eat_times(void *arg)
// {
// 	t_data *data;
// 	int j;

// 	data = (t_data *)arg;
// 	while (data->n_times)
// 	{
// 		sem_wait(data->lock);
// 		data->n_times--;
// 		sem_post(data->lock);
// 	}
// 	j = 0;
// 	while (j < data->total_ph)
// 		kill(data->pid[j++], SIGKILL);
// 	free(data->pid);
// 	exit(0);
// }

void add_threads(t_data *data)
{
	int id;
	int j;
	// pthread_t time_eat;

	data->pid = malloc(sizeof(pthread_t) * (data->total_ph));
	if (data->pid == NULL)
		exit(ERROR);
	id = 0;
	data->wait = 0;
	data->start_t = get_time();
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
	// printf("%d\n\n\n\n\n\n\n", data->wait);
	// if (data->n_t_m_eat)
	// {
	// 	data->n_times = data->n_t_m_eat;
	// 	pthread_create(&time_eat, NULL, check_eat_times, data);
	// }
	while (waitpid(0, NULL, 0) > 0)
	{
		j = 0;
		while (j < data->total_ph)
			kill(data->pid[j++], SIGKILL);
		free(data->pid);
		sem_post(data->lock);
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

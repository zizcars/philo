/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managment_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/16 11:38:28 by achakkaf         ###   ########.fr       */
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

void add_threads(t_data *data)
{
	int id;
	pid_t *pid;
	int j;

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
	while (waitpid(0, NULL, 0) > 0)
	{
		j = 0;
		while(j < data->total_ph)
			kill(pid[j++], SIGKILL);
		free(pid);
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

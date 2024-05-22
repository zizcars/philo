/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managment_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/22 17:06:03 by achakkaf         ###   ########.fr       */
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

void print_message(char *message, t_philo *philo, long print_time)
{
	// long start;

	// start = get_time();
	sem_wait(philo->data->print);
	printf("%ld %d %s\n", print_time - philo->data->start_t, philo->id, message);
	sem_post(philo->data->print);
}

void mssleep(int time_ms)
{
	long start;

	start = get_time();
	while (get_time() - start < time_ms)
		usleep(85);
}

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

void *death(void *arg)
{
	t_philo *philo;
	long start;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->sem_fast);
		start = get_time();
		if (philo->last_meal != -1 && start - check_last_meal(philo, 0) >= philo->data->t_die)
		{
			sem_wait(philo->data->lock);
			sem_wait(philo->data->print);
			sem_post(philo->data->sem_fast);
			printf("\e[31m%ld %d is died\n", start - philo->data->start_t, philo->id);
			exit(DIED);
		}
		sem_post(philo->data->sem_fast);
	}
	return (NULL);
}

void philosopher(t_philo *philo)
{
	pthread_t checker;
	int one_time = 1;

	philo->last_meal = -1;
	sem_unlink("sem_last_meal");
	philo->sem_last_meal = sem_open("sem_last_meal",O_CREAT  | O_EXCL, 0644, 1);
	if (philo->sem_last_meal == SEM_FAILED)
		exit(ERROR);
	pthread_create(&checker, NULL, death, philo);
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
	exit(0);
}

void add_threads(t_data *data)
{
	int id;
	int j;

	data->pid = malloc(sizeof(pthread_t) * (data->total_ph));
	if (data->pid == NULL)
		exit(ERROR);
	id = 0;
	data->start_t = get_time();
	while (id < data->total_ph)
	{
		data->pid[id] = fork();
		if (data->pid[id] == -1)
		{
			j = 0;
			while (j < id)
				kill(data->pid[j++], SIGKILL);
			free(data->pid);
			exit(ERROR);
		}
		else if (data->pid[id] == 0)
		{
			philosopher(&data->philos[id]);
		}
		id++;
	}
	while (id--)
		sem_post(data->sem_start);
	while (waitpid(0, NULL, 0) > 0)
	{
		j = 0;
		while (j < data->total_ph)
			kill(data->pid[j++], SIGKILL);
		free(data->pid);
		sem_close(data->lock);
		sem_close(data->print);
		sem_unlink("sem_process_count");
		sem_unlink("sem_start");
		sem_unlink("lock");
		sem_unlink("print");
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

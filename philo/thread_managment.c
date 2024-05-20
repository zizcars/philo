/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/20 12:36:03 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time(void)
{
	struct timeval time_now;

	if (gettimeofday(&time_now, NULL))
		return (ERROR);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

void print_message(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead != DIED)
		printf("%ld %d %s\n", get_time() - philo->data->start_t, philo->id, message);
	pthread_mutex_unlock(&philo->data->lock);
}

// void mssleep(int time_ms)
// {
// 	long start, end;
// 	long elapsed;
// 	start = get_time();
//     usleep(7 * (time_ms / 8) * 1000);
// 	end = get_time();
//     time_ms = time_ms - (end - start);
// 	while (time_ms > 0)
// 	{
// 		start = get_time();
// 		usleep(100);
// 		// if (check_death(philo) == DIED)
// 		// 	return (DIED);
// 		end = get_time();
// 		elapsed = end - start;
// 		time_ms -= elapsed;
// 	}
// return (LIFE);
// }

void mssleep(int time_to_sleep, t_philo *philo)
{
	long start;

	start = get_time();
	while ((get_time() - start) < time_to_sleep)
	{
		usleep(100);
		if (check_death(philo) == DIED)
			return;
	}
}

void *philosopher(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (check_death(philo) == LIFE && philo->n_times != 0)
	{
		if (philo->state == go_eat)
			eating(philo);
		else
			sleeping(philo);
	}
	return (NULL);
}

int add_threads(t_data *data)
{
	int id;
	pthread_t *threads;

	threads = malloc(sizeof(pthread_t) * (data->total_ph));
	if (threads == NULL)
		return (ERROR);
	id = 0;
	data->start_t = get_time();
	while (id < data->total_ph)
	{
		update_last_meal(&data->philos[id], 1);
		if (pthread_create(&threads[id], NULL, philosopher, &data->philos[id]))
		{
			free(threads);
			return (ERROR);
		}
		id++;
	}
	monitor(data);
	if (join_free(data, threads) == ERROR)
		return (GOOD);
	return (GOOD);
}

int join_free(t_data *data, pthread_t *threads)
{
	int i;

	i = 0;
	while (i < data->total_ph)
	{
		if (pthread_join(threads[i++], NULL))
		{
			free(threads);
			return (ERROR);
		}
	}
	i = 0;
	while (i < data->total_ph)
		pthread_detach(threads[i++]);
	free(threads);
	return (GOOD);
}

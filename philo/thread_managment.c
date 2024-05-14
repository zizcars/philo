/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/14 19:12:46 by achakkaf         ###   ########.fr       */
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
		printf("%ld %d %s\n", get_time() - philo->start, philo->id, message);
	pthread_mutex_unlock(&philo->data->lock);
}

int ft_sleep(int time_ms, t_philo *philo)
{
	long start, end;
	long elapsed;

	while (time_ms > 0)
	{
		start = get_time();
		usleep(1000);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->dead == DIED)
		{
			pthread_mutex_unlock(&philo->data->lock);
			return (DIED);
		}
		pthread_mutex_unlock(&philo->data->lock);
		end = get_time();
		elapsed = end - start;
		time_ms -= elapsed;
	}
	return (LIFE);
}

void *philosopher(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(100);
	philo->start = get_time();
	while (check_n_times(philo->data) == GOOD && check_death(philo) == LIFE)
	{
		if (philo->data->n_t_m_eat && check_n_times(philo->data) == GOOD)
		{
			pthread_mutex_lock(&philo->data->lock_n_times);
			philo->data->n_times--;
			pthread_mutex_unlock(&philo->data->lock_n_times);
		}
		print_message("is thinking", philo);
		routine(philo);
	}
	return (NULL);
}
// 5 800 200 200 7 test that
int add_threads(t_data *data)
{
	int i;
	int id;
	pthread_t *threads;

	threads = malloc(sizeof(pthread_t) * (data->total_ph + 1));
	if (threads == NULL)
		return (ERROR);
	i = 0;
	pthread_create(&threads[i++], NULL, monitor, data);
	id = 0;
	while (id < data->total_ph)
	{
		pthread_create(&threads[i], NULL, philosopher, &data->philos[id++]);
		i++;
	}
	i = 0;
	while (i < data->total_ph + 1)
	{
		pthread_join(threads[i], NULL);
		i++;
	}

	// destroy all thread
	free(threads);
	return (0);
}

int check_n_times(t_data *data)
{
	pthread_mutex_lock(&data->lock_n_times);
	if (data->n_times <= 0)
	{
		pthread_mutex_unlock(&data->lock_n_times);
		return (-1);
	}
	pthread_mutex_unlock(&data->lock_n_times);
	return (GOOD);
}
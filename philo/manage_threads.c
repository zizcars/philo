/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/11 18:55:34 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_time(struct timeval start_t)
{
	struct timeval end_t;

	if (gettimeofday(&end_t, NULL))
		return (-1);
	return ((end_t.tv_sec - start_t.tv_sec) * 1000 + (end_t.tv_usec - start_t.tv_usec) / 1000);
}

int ft_sleep(t_philo *philo, int time_ms)
{
	struct timeval start, end;
	long elapsed;

	time_ms *= 1000;
	while (time_ms > 0)
	{
   		gettimeofday(&start, NULL);
		usleep(100);
		if (died(philo) == DIED)
			return (DIED);
		gettimeofday(&end, NULL);
		elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
		time_ms -= elapsed;
	}
	return (LIFE);
}

void *philosopher(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int n_times;

	if (philo->n_t_m_eat == 0)
		n_times = 1;
	else 
		n_times = philo->n_t_m_eat;
	gettimeofday(&philo->start, NULL);
	while (n_times)
	{
		printf("%d %d is thinking\n", get_time(philo->start), philo->id);
		gettimeofday(&philo->start_t, NULL);
		if (eating(philo, philo->start) == DIED)
			break;
		gettimeofday(&philo->start_t, NULL);	
		printf("%d %d is sleeping\n", get_time(philo->start), philo->id);
		int check = ft_sleep(philo, philo->t_sleep);
		if (died(philo) == DIED || check == DIED)
			break;
		if (philo->n_t_m_eat)
			n_times--;
	}
	return (NULL);
}

int create_threads(t_philo *philo)
{
	int i;
	pthread_t *threads;

	threads = malloc(sizeof(pthread_t) * philo->total_ph);
	i = 0;
	while (i < philo->total_ph)
	{
		pthread_create(&threads[i], NULL, philosopher, philo);
		if (i % 2 == 0)
			usleep(100);
		philo = philo->next;
		i++;
	}
	i = 0;
	while (i < philo->total_ph)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (0);
}

// int check_died(t_philo *philo)
// {
// 	int i;
// 	i = 0;
// 	while (i < philo->total_ph)
// 	{
// 		pthread_mutex_lock(&philo->mutex_lock);
// 		if (philo->stop == DIED)
// 		{
// 			pthread_mutex_unlock(&philo->mutex_lock);
// 			return (DIED);
// 		}
// 		pthread_mutex_unlock(&philo->mutex_lock);
// 		philo = philo->next;
// 		i++;
// 	}
// 	return (LIFE);
// }

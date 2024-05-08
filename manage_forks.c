/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/08 20:29:49 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_time(struct timeval start_t)
{
	int time;
	struct timeval end_t;
	if (gettimeofday(&end_t, NULL))
		return (-1);
	time = (end_t.tv_sec - start_t.tv_sec) * 1000 + (end_t.tv_usec - start_t.tv_usec) / 1000;
	return (time);
}

void eating(t_philo *philo, struct timeval start)
{
	pthread_mutex_lock(&philo->r_fork);
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->next->l_fork);

	// eating
	printf("%d %d is eating\n", get_time(start), philo->id);
	usleep(philo->t_eat * 1000); // eating for 1 second

	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->next->l_fork);
}

void *philosopher(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int time;
	struct timeval start;
	gettimeofday(&start, NULL);
	while (1) // philosophers will keep thinking and eating indefinitely
	{
		// thinking
		gettimeofday(&philo->start_t, NULL);
		printf("%d %d is thinking\n", get_time(start), philo->id);
		// hungry
		printf("%d %d has taken a fork\n", get_time(start), philo->id);
		
		eating(philo, start);
		
		time = get_time(philo->start_t);
		
		gettimeofday(&philo->tmp, NULL);
		if (time >= philo->t_die)
		{
			printf("%d %d died\n", get_time(philo->tmp), philo->id);
			philo->stop = 0;
			return (NULL);
		}

		printf("%d %d is sleeping\n", get_time(start), philo->id);
		usleep(philo->t_sleep * 1000);

		time = get_time(philo->start_t);
		gettimeofday(&philo->tmp, NULL);
		if (time >= philo->t_die)
		{
			printf("%d %d died\n", get_time(philo->tmp), philo->id);
			philo->stop = 0;
			return (NULL);
		}
	}
	return (NULL);
}

int check_died(t_philo *philo)
{
	int i;
	t_philo *tmp;

	tmp = philo;
	i = 0;
	while (i < tmp->total_ph)
	{
		if (tmp->stop == 0)
			return (0);
		i++;
		tmp = tmp->next;
	}
	return (1);
}

int create_threads(t_philo *philo)
{
	int i;
	pthread_t *threads;

	threads = malloc(sizeof(pthread_t) * philo->total_ph);
	i = 0;
	while (i < philo->total_ph && check_died(philo))
	{
		pthread_create(&threads[i], NULL, philosopher, philo);
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

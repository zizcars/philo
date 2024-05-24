/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/24 11:35:25 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_data *data)
{
	int	id;

	while (1)
	{
		id = 0;
		while (id < data->total_ph)
		{
			if (data->n_t_m_eat)
			{
				if (check_n_times(&data->philos[id], 0) == DIED)
					return ;
			}
			if (get_time() - last_meal(&data->philos[id], 0) >= data->t_die)
			{
				pthread_mutex_lock(&data->lock);
				data->dead = DIED;
				printf("\e[31m%ld %d is died\n", \
					get_time() - data->start_t, data->philos[id].id);
				pthread_mutex_unlock(&data->lock);
				return ;
			}
			id++;
			usleep(800);
		}
	}
}

void	print_message(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead != DIED)
		printf("%ld %d %s\n", \
			get_time() - philo->data->start_t, philo->id, message);
	pthread_mutex_unlock(&philo->data->lock);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_death(philo) == LIFE && philo->n_times != 0)
	{
		if (philo->state == go_eat)
			eating(philo);
		else
			sleeping(philo);
	}
	return (NULL);
}

int	add_threads(t_data *data)
{
	int			id;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * (data->total_ph));
	if (threads == NULL)
		return (ERROR);
	id = 0;
	data->start_t = get_time();
	while (id < data->total_ph)
	{
		last_meal(&data->philos[id], 1);
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

int	join_free(t_data *data, pthread_t *threads)
{
	int	i;

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

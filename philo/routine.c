/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:27:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/14 14:54:39 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->write);
	if (philo->data->dead == DIED)
	{
		pthread_mutex_unlock(&philo->write);
		return;
	}
	pthread_mutex_unlock(&philo->write);
	take_forks(philo);
	print_message("is eating", philo);
	ft_sleep(philo->data->t_eat, philo);
	philo->last_meal = get_time();
	put_forks(philo);
	print_message("is sleeping", philo);
	ft_sleep(philo->data->t_sleep, philo);
}
int check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->write);
	if (philo->data->dead == DIED)
	{
		pthread_mutex_unlock(&philo->write);
		return (DIED);
	}
	pthread_mutex_unlock(&philo->write);
	return (LIFE);
}

void take_forks(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->waiter);

	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo);
	// pthread_mutex_unlock(&philo->data->waiter);
	philo->is_eating = EATING;
}

void put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->is_eating = NOT_EATING;
}

void *monitor(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;

	while (data->dead == LIFE)
	{
		i = 0;
		while (i < data->total_ph)
		{
			pthread_mutex_lock(&data->philos[i].write);
			if (get_time() - data->philos[i].last_meal > data->t_die)
			{
				data->dead = DIED;
				printf("%ld %d is died\n", get_time() - data->philos[i].last_meal, data->philos[i].id);
				pthread_mutex_unlock(&data->philos[i].write);
				break;
			}
			pthread_mutex_unlock(&data->philos[i].write);
			i++;
		}
	}
	return (NULL);
}

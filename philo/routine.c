/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:27:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/15 11:59:54 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead == DIED)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return;
	}
	pthread_mutex_unlock(&philo->data->lock);
	take_forks(philo);
	if (philo->is_eating == EATING && check_n_times(philo->data) == GOOD)
	{
		if (check_n_times(philo->data) == GOOD && philo->data->n_t_m_eat)
		{
			pthread_mutex_lock(&philo->data->lock_n_times);
			philo->data->n_times--;
			pthread_mutex_unlock(&philo->data->lock_n_times);
		}
		print_message("is eating", philo);
		ft_sleep(philo->data->t_eat, philo);
		if (check_n_times(philo->data) != GOOD)
		{
			pthread_mutex_lock(&philo->data->lock_n_times);
			philo->data->stop = 0;
			pthread_mutex_unlock(&philo->data->lock_n_times);
		}
		pthread_mutex_lock(&philo->data->lock);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->data->lock);
		put_forks(philo);
		print_message("is sleeping", philo);
		ft_sleep(philo->data->t_sleep, philo);
	}
	put_forks(philo);
}

int check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead == DIED)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (DIED);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (LIFE);
}

void take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo);
	if (philo->data->total_ph == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		while (check_death(philo) == LIFE)
			;
	}
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo);
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

	while (data->dead == LIFE && check_stop(data) == GOOD) // this is a problem
	{
		i = 0;
		while (i < data->total_ph && check_stop(data) == GOOD) // there is a problem here
		{
			pthread_mutex_lock(&data->lock);
			if (get_time() - data->philos[i].last_meal > data->t_die)
			{
				data->dead = DIED;
				printf("%ld %d is died\n", get_time() - data->philos[i].last_meal, data->philos[i].id);
				pthread_mutex_unlock(&data->lock);
				break;
			}
			pthread_mutex_unlock(&data->lock);
			i++;
		}
	}
	return (NULL);
}

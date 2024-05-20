/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:27:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/20 13:02:49 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_n_times(t_philo *philo, int update)
{
	pthread_mutex_lock(&philo->n_times_mtx);
	if (update)
		philo->n_times--;
	else
	{
		if (philo->n_times == 0)
		{
			pthread_mutex_unlock(&philo->n_times_mtx);
			return (DIED);
		}
	}
	pthread_mutex_unlock(&philo->n_times_mtx);
	return (LIFE);
}

void sleeping(t_philo *philo)
{
	print_message("is sleeping", philo);
	mssleep(philo->data->t_sleep, philo);
	philo->state = go_eat;
}

long update_last_meal(t_philo *philo, int write)
{
	long last_meal;
	pthread_mutex_lock(&philo->meal_mtx);
	if (write)
		philo->last_meal = get_time();
	else
	{
		last_meal = philo->last_meal;
		pthread_mutex_unlock(&philo->meal_mtx);
		return (last_meal);
	}
	pthread_mutex_unlock(&philo->meal_mtx);
	return (-1);
}

void eating(t_philo *philo)
{
	print_message("is thinking", philo);
	if (check_death(philo) == DIED)
		return;
	take_forks(philo);
	print_message("is eating", philo);
	mssleep(philo->data->t_eat, philo);
	if (philo->data->n_t_m_eat != 0)
		check_n_times(philo, 1);
	update_last_meal(philo, 1);
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
}

void put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->state = go_sleep;
}

void monitor(t_data *data)
{
	int id;

	while (1)
	{
		id = 0;
		while (id < data->total_ph)
		{
			if (data->n_t_m_eat)
			{
				if (check_n_times(&data->philos[id], 0) == DIED)
					return;
			}
			if (get_time() - update_last_meal(&data->philos[id], 0) >= data->t_die)
			{
				pthread_mutex_lock(&data->lock);
				data->dead = DIED;
				printf("\e[31m%ld %d is died\n", get_time() - data->start_t, data->philos[id].id);
				pthread_mutex_unlock(&data->lock);
				return;
			}
			id++;
		}
	}
}

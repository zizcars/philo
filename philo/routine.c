/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:27:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/24 11:35:33 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	print_message("is sleeping", philo);
	mssleep(philo->data->t_sleep, philo);
	philo->state = go_eat;
}

long	last_meal(t_philo *philo, int write)
{
	long	last_meal;

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

void	eating(t_philo *philo)
{
	print_message("is thinking", philo);
	if (check_death(philo) == DIED)
		return ;
	take_forks(philo);
	print_message("is eating", philo);
	mssleep(philo->data->t_eat, philo);
	if (philo->data->n_t_m_eat != 0)
		check_n_times(philo, 1);
	last_meal(philo, 1);
	put_forks(philo);
}

void	take_forks(t_philo *philo)
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

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->state = go_sleep;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:27:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/22 19:53:45 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void sleeping(t_philo *philo)
{
	print_message("is sleeping", philo, get_time());
	mssleep(philo->data->t_sleep);
	philo->state = go_eat;
}

static void take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_message("has taken a fork", philo, get_time());
	if (philo->data->total_ph == 1)
	{
		while (get_time() - philo->last_meal < philo->data->t_die);
		sem_post(philo->data->forks);
		printf("\e[31m%ld %d is died\n\e[0m", get_time() - philo->data->start_t, philo->id);
		exit(EXIT_SUCCESS);
	}
	sem_wait(philo->data->forks);
	print_message("has taken a fork", philo, get_time());
}

static void put_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	philo->state = go_sleep;
}

void eating(t_philo *philo)
{
	print_message("is thinking", philo, get_time());
	take_forks(philo);
	print_message("is eating", philo, get_time());
	check_last_meal(philo, 1);
	mssleep(philo->data->t_eat);
	if (philo->data->n_t_m_eat)
		philo->n_times_eat--;
	put_forks(philo);
}

void *death_checker(void *arg)
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
			exit(EXIT_SUCCESS);
		}
		sem_post(philo->data->sem_fast);
	}
	return (NULL);
}


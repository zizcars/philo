/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:27:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/16 11:17:33 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void routine(t_philo *philo)
{
	take_forks(philo);
	if (philo->is_eating == EATING)
	{
		print_message("is eating", philo);
		ft_sleep(philo->data->t_eat, philo);
		philo->last_meal = get_time();
		put_forks(philo);
		print_message("is sleeping", philo);
		ft_sleep(philo->data->t_sleep, philo);
	}
}

void take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_message("has taken a right fork", philo);
	if (philo->data->total_ph == 1)
	{
		sem_post(philo->data->forks);
		exit(GOOD);
	}
	else
	{
		sem_wait(philo->data->forks);
		print_message("has taken a left fork", philo);
		philo->is_eating = EATING;
	}
}

void put_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	// print_message("has put a right fork", philo);
	sem_post(philo->data->forks);
	// print_message("has put a left fork", philo);
	philo->is_eating = NOT_EATING;
}

int monitor(t_data *data)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < data->total_ph)
		{
			if (get_time() - data->philos[i].last_meal > data->t_die)
			{
				printf("\e[31m%ld %d is died\n\e[0m", get_time() - data->philos[i].last_meal, data->philos[i].id);
				return (DIED);
			}
			i++;
		}
	}
	return (LIFE);
}

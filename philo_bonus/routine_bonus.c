/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:27:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/20 17:00:50 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void sleeping(t_philo *philo)
{
	print_message("is sleeping", philo);
	mssleep(philo->data->t_sleep);
	philo->state = go_eat;
}

void eating(t_philo *philo)
{
	print_message("is thinking", philo);
	take_forks(philo);
	print_message("is eating", philo);
	philo->last_meal = get_time();
	mssleep(philo->data->t_eat);
	put_forks(philo);
}

void take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_message("has taken a fork", philo);
	if (philo->data->total_ph == 1)
	{
		sem_post(philo->data->forks);
		exit(GOOD);
	}
	sem_wait(philo->data->forks);
	print_message("has taken a fork", philo);
}

void put_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	philo->state = go_sleep;
}

// int monitor(t_data *data)
// {
// 	int i;

// 	while (1)
// 	{
// 		i = 0;
// 		while (i < data->total_ph)
// 		{
// 			if (get_time() - data->philos[i].last_meal > data->t_die)
// 			{
// 				printf("\e[31m%ld %d is died\n\e[0m", get_time() - data->start_t, data->philos[i].id);
// 				return (DIED);
// 			}
// 			i++;
// 		}
// 	}
// 	return (LIFE);
// }

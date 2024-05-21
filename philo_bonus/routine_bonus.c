/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:27:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/21 18:44:39 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void sleeping(t_philo *philo)
{
	print_message("is sleeping", philo, get_time());
	mssleep(philo->data->t_sleep);
	// philo->end_sleeping = get_time();
	philo->state = go_eat;
}

void eating(t_philo *philo)
{
	// long start;

	print_message("is thinking", philo, get_time());
	take_forks(philo);
	// philo->end_thinking = get_time();/
	// start = get_time();
	print_message("is eating", philo, get_time());
	// start = get_time();
	philo->last_meal = get_time();
	mssleep(philo->data->t_eat);
	// philo->end_eating = get_time();
	// printf("%ld\n", get_time() - start);
	// exit(0);
	put_forks(philo);
}

void take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_message("has taken a fork", philo, get_time());
	if (philo->data->total_ph == 1)
	{
		while (get_time() - philo->last_meal < philo->data->t_die);
		sem_post(philo->data->forks);
		printf("\e[31m%ld %d is died\n\e[0m", get_time() - philo->data->start_t, philo->id);
		exit(DIED);
	}
	sem_wait(philo->data->forks);
	print_message("has taken a fork", philo, get_time());
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

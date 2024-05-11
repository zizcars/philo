/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:27:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/11 12:02:10 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int eating(t_philo *philo, struct timeval start)
{
	// this protaction for dieing in thinking this case ./philo 5 100 200 50
	sem_wait(philo->mutex);
	sem_wait(philo->semaphore);
	printf("%d %d has taken a fork\n", get_time(start), philo->id);
	if (died(philo) == DIED)
	{
		sem_post(philo->semaphore);
		sem_post(philo->mutex);
		// sem_post(philo->semaphore);
		return (DIED);
	}
	// if you moves the simulation will stop in the test of ./philo 1 100 ...
	//./philo 3 600 200 200
	// sem_wait(philo->semaphore);
	// printf("helo\n");
	if (died(philo) == DIED)
	{
		// sem_post(philo->semaphore);
		sem_post(philo->semaphore);
		sem_post(philo->mutex);
		return (DIED);
	}
	// if the number of philosophers equale 1
	printf("%d %d has taken a fork\n", get_time(start), philo->id);
	printf("%d %d is eating\n", get_time(start), philo->id);
	// int check = ;
	if (ft_sleep(philo, philo->t_eat) == DIED)
	{
		// sem_post(philo->semaphore);
		sem_post(philo->semaphore);
		sem_post(philo->mutex);
		return (DIED);
	}
	// sem_post(philo->semaphore);
	sem_post(philo->semaphore);
	sem_post(philo->mutex);
	return (LIFE);
}

// void change_print_state(t_philo *philo)
// {
// 	int i;
// 	t_philo *tmp;

// 	i = 0;
// 	tmp = philo;
// 	while (i < tmp->total_ph)
// 	{
// 		pthread_mutex_lock(&tmp->print_mutex);
// 		tmp->print_message = 0;
// 		tmp = tmp->next;
// 		i++;
// 		pthread_mutex_unlock(&tmp->print_mutex);
// 	}
// }

int died(t_philo *philo)
{
	int i;
	// t_philo *tmp;
	// int check = 0;
	i = 0;
	// tmp = philo;
	// while (i < tmp->total_ph)
	// {
	// 	pthread_mutex_lock(&tmp->mutex_lock);
	// 	if (tmp->stop == DIED)
	// 	{
	// 		check = DIED;
	// 		pthread_mutex_unlock(&tmp->mutex_lock);
	// 		break;
	// 	}
	// 	pthread_mutex_unlock(&tmp->mutex_lock);
	// 	tmp = tmp->next;
	// 	i++;
	// }
	// printf("sd\n");
	sem_wait(philo->lock);
	if (get_time(philo->start_t) > philo->t_die || philo->total_ph == 1)
		philo->stop = DIED;
	if (philo->stop == DIED)
	{
		if (philo->print_message == 1)
		{
			printf("%d %d died\n", get_time(philo->start_t), philo->id);
			philo->print_message = 0;
			// change_print_state(philo);
		}
		sem_post(philo->lock);
		return (DIED);
	}
	sem_post(philo->lock);
	return (LIFE);
}

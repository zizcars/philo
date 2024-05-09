/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:27:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/09 17:54:53 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int eating(t_philo *philo, struct timeval start)
{
	// this protaction for dieing in thinking this case ./philo 5 100 200 50
	pthread_mutex_lock(&philo->r_fork);
	printf("%d %d has taken a fork\n", get_time(start), philo->id);
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->next->l_fork);
	if (died(philo) == DIED) // || check_died(philo) == DIED)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
		// pthread_mutex_unlock(&philo->next->l_fork);
		return (DIED);
	}
	// if the number of philosophers equale 1
	printf("%d %d has taken a fork\n", get_time(start), philo->id);
	printf("%d %d is eating\n", get_time(start), philo->id);
	// int check = ft_sleep(philo, philo->t_eat);
	// if (check == DIED)
	// {
	// 	gettimeofday(&philo->start_t, NULL);
	// 	pthread_mutex_unlock(&philo->r_fork);
	// 	pthread_mutex_unlock(&philo->l_fork);
	// 	pthread_mutex_unlock(&philo->next->l_fork);
	// 	return (DIED);
	// }
	usleep(philo->t_sleep * 1000);
	// gettimeofday(&philo->start_t, NULL);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->next->l_fork);
	return (LIFE);
}

void change_print_state(t_philo *philo)
{
	int i;
	t_philo *tmp;

	i = 0;
	tmp = philo;
	while (i < tmp->total_ph)
	{
		pthread_mutex_lock(&tmp->print_mutex);
		tmp->print_message = 0;
		pthread_mutex_unlock(&tmp->print_mutex);
		tmp = tmp->next;
		i++;
	}
}

int died(t_philo *philo)
{
	int i;
	t_philo *tmp;
	int check = 0;
	i = 0;
	tmp = philo;
	while (i < tmp->total_ph)
	{
		pthread_mutex_lock(&tmp->mutex_lock);
		if (tmp->stop == DIED)
		{
			check = DIED;
			pthread_mutex_unlock(&tmp->mutex_lock);
			break;
		}
		pthread_mutex_unlock(&tmp->mutex_lock);
		tmp = tmp->next;
		i++;
	}
	pthread_mutex_lock(&philo->mutex_lock);
	if (get_time(philo->start_t) >= philo->t_die || philo->total_ph == 1)
		philo->stop = DIED;
	if (philo->stop == DIED || check == DIED)
	{
		if (philo->print_message == 1)
		{
			printf("%d %d died\n", get_time(philo->start_t), philo->id);
			change_print_state(philo);
		}
		pthread_mutex_unlock(&philo->mutex_lock);
		return (DIED);
	}
	pthread_mutex_unlock(&philo->mutex_lock);
	return (LIFE);
}

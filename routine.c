/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:27:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/10 13:07:06 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int eating(t_philo *philo, struct timeval start)
{
	// this protaction for dieing in thinking this case ./philo 5 100 200 50
	pthread_mutex_lock(&philo->r_fork);
	printf("%d %d has taken a fork\n", get_time(start), philo->id);
	pthread_mutex_lock(&philo->l_fork);
	if (died(philo) == DIED)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
		return (DIED);
	}
	//if you moves the simulation will stop in the test of ./philo 1 100 ... 
	//./philo 3 600 200 200 
	pthread_mutex_lock(&philo->next->l_fork);
	if (died(philo) == DIED)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(&philo->next->l_fork);
		return (DIED);
	}
	// if the number of philosophers equale 1
	printf("%d %d has taken a fork\n", get_time(start), philo->id);
	printf("%d %d is eating\n", get_time(start), philo->id);
	// int check = ;
	if ( ft_sleep(philo, philo->t_eat) == DIED)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(&philo->next->l_fork);
		return (DIED);
	}
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
	// lock_all(philo);
	while (i < tmp->total_ph)
	{
		pthread_mutex_lock(&tmp->print_mutex);
		tmp->print_message = 0;
		tmp = tmp->next;
		i++;
		pthread_mutex_unlock(&tmp->print_mutex);
	}
	// unlock_all(philo);
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
	if (get_time(philo->start_t) > philo->t_die || philo->total_ph == 1)
		philo->stop = DIED;
	if (philo->stop == DIED || check == DIED)
	{
		if (philo->print_message == 1)
		{
			// lock_all(philo);
			printf("%d %d died\n", get_time(philo->start_t), philo->id);
			change_print_state(philo);
			// unlock_all(philo);
		}
		pthread_mutex_unlock(&philo->mutex_lock);
		return (DIED);
	}
	pthread_mutex_unlock(&philo->mutex_lock);
	return (LIFE);
}
void lock_all(t_philo *philo)
{
	int i;
	t_philo *tmp;

	tmp = philo;
	i = 0;
	while(i < philo->total_ph)
	{
		pthread_mutex_lock(&tmp->print_mutex);
		i++;
		tmp = tmp->next;
	}
}
void unlock_all(t_philo *philo)
{
	int i;
	t_philo *tmp;

	tmp = philo;
	i = 0;
	while(i < philo->total_ph)
	{
		pthread_mutex_unlock(&tmp->print_mutex);
		tmp = tmp->next;
		i++;
	}
}
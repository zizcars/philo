/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/07 19:10:15 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// remamber to handel the max of thread in your machine

// void *eating(void *arg);
// void *sleeping(void *arg);
// // void *thinking(void *arg);

// void *eating(void *arg)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)arg;
// 	if (philo->n_ph > philo->next->n_ph)
// 	{
// 		pthread_mutex_lock(&philo->lock);
// 		pthread_mutex_lock(&philo->next->lock);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&philo->next->lock);
// 		pthread_mutex_lock(&philo->lock);
// 	}
// 	if (philo->state == THINKING && philo->n_fork == 1 && philo->next->n_fork == 1)
// 	{
// 		philo->n_fork += 1;
// 		philo->next->n_fork -= 1;
// 		philo->state = EATING;
// 		usleep(philo->philo_info.t_eat * 1000);
// 	}
// 	printf("%d\t%d\t%d\n", philo->n_ph, philo->n_fork, philo->state);
// 	printf("->%d\t%d\t%d\n", philo->next->n_ph, philo->next->n_fork, philo->next->state);
// 	pthread_mutex_unlock(&philo->next->lock);
// 	pthread_mutex_unlock(&philo->lock);
// 	sleeping(philo);
// 	return (NULL);
// }

// void *sleeping(void *arg)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)arg;
// 	if (philo->n_ph > philo->next->n_ph)
// 	{
// 		pthread_mutex_lock(&philo->lock);
// 		pthread_mutex_lock(&philo->next->lock);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&philo->next->lock);
// 		pthread_mutex_lock(&philo->lock);
// 	}
// 	if (philo->state == EATING)
// 	{
// 		philo->n_fork -= 1;
// 		philo->next->n_fork += 1;
// 		philo->state = SLEEPING;
// 		usleep(philo->philo_info.t_sleep * 1000);
// 	}
// 	pthread_mutex_unlock(&philo->next->lock);
// 	pthread_mutex_unlock(&philo->lock);
// 	// printf("%d\t%d\t%d\n", philo->n_ph, philo->n_fork, philo->state);
// 	// printf("->%d\t%d\t%d\n", philo->next->n_ph, philo->next->n_fork, philo->next->state);
// 	// thinking(philo);
// 	return (NULL);
// }

// int pick_fork(t_philo *philo)
// {
// 	if (philo->n_fork)
// }

// void *steps(void *arg)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)arg;

// 	while (1)
// 	{
// 		usleep(philo->philo_info.t_die / 10);
// 		pick_fork(philo);
// 		usleep(philo->philo_info.t_die / 5);
// 	}
// 	return (NULL);
// }

// int create_threads(t_philo *philo)
// {
// 	pthread_t *threads;
// 	int i;

// 	threads = malloc(sizeof(pthread_t) * (philo->n_ph - 1));
// 	i = 0;
// 	while (i < philo->philo_info.total_ph)
// 	{
// 		pthread_create(&threads[i], NULL, steps, philo);
// 		philo = philo->next;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < philo->philo_info.total_ph)
// 	{
// 		pthread_join(threads[i], NULL);
// 		i++;
// 	}
// 	free(threads);
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/08 17:18:43 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    while (1) // philosophers will keep thinking and eating indefinitely
    {
        // thinking
        printf("Philosopher %d is thinking.\n", philo->id);
        // hungry
        pthread_mutex_lock(&philo->r_fork);
        pthread_mutex_lock(&philo->l_fork);
        pthread_mutex_lock(&philo->next->l_fork);

        // eating
        printf("Philosopher %d is eating.\n", philo->id);
        usleep(philo->t_eat * 1000); // eating for 1 second

        pthread_mutex_unlock(&philo->r_fork);
        pthread_mutex_unlock(&philo->l_fork);
        pthread_mutex_unlock(&philo->next->l_fork);
        printf("Philosopher %d is sleeping.\n", philo->id);
        usleep(philo->t_sleep * 1000);
    }
}

int create_threads(t_philo *philo)
{
    pthread_t *threads;
    int i;

    threads = malloc(sizeof(pthread_t) * philo->total_ph);
    i = 0;
    while (i < philo->total_ph)
    {
        pthread_create(&threads[i], NULL, philosopher, philo);
        philo = philo->next;
        i++;
    }
    i = 0;
    while (i < philo->total_ph)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    free(threads);
    return (0);
}

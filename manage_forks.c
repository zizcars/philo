/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/09 17:55:53 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief calculte time in ms 
/// @param start_t start point
/// @return time from start in ms
int get_time(struct timeval start_t)
{
	int time;
	struct timeval end_t;

	if (gettimeofday(&end_t, NULL))
		return (-1);
	time = (end_t.tv_sec - start_t.tv_sec) * 1000 + (end_t.tv_usec - start_t.tv_usec) / 1000;
	return (time);
}

/// @brief sleep and check if there is an error 
/// @param philo 
/// @param time_us 
/// @return 
// int	ft_sleep(t_philo *philo, int time_us)
// {
// 	// (void )philo;
// 	time_us *= 1000;
// 	while (time_us > 0)
// 	{
// 		usleep(1000);
// 		if (died(philo) == DIED)
// 			return (DIED);
// 		time_us -= 1000;
// 	}
// 	// usleep(time_us * 1000);
// 	return (LIFE);
// }
#include <sys/time.h>

int ft_sleep(t_philo *philo, int time_ms)
{
    struct timeval start, end;
    long elapsed;

    // Get the start time
    gettimeofday(&start, NULL);
    time_ms *= 1000;
    while (time_ms > 0)
    {
        usleep(100); // Sleep for 100 microseconds
        if (died(philo) == DIED)
            return (DIED);

        // Get the end time
        gettimeofday(&end, NULL);

        // Calculate the elapsed time in microseconds
        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

        // Subtract the elapsed time from the total sleep time
        time_ms -= elapsed;

        // Update the start time for the next iteration
        start = end;
    }
	// usleep(time_ms);
    return (LIFE);
}

void *philosopher(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int n_times;

	if (philo->n_t_m_eat == 0)
		n_times = 1;
	else 
		n_times = philo->n_t_m_eat;
	gettimeofday(&philo->start, NULL);
	while (n_times)
	{
		printf("%d %d is thinking\n", get_time(philo->start), philo->id);
		gettimeofday(&philo->start_t, NULL);
		if (eating(philo, philo->start) == DIED)
			break;
		gettimeofday(&philo->start_t, NULL);	
		// time = get_time(philo->start_t);
		// printf("|%d->%d|\n",philo->id,get_time(philo->start_t));
		// if (died(philo) == DIED)// || check_died(philo) == DIED)
		// 	break;
		printf("%d %d is sleeping\n", get_time(philo->start), philo->id);
		int check = ft_sleep(philo, philo->t_sleep);
		// time = ;
		if (died(philo) == DIED || check == DIED)// || check_died(philo) == DIED)
			break;
		if (philo->n_t_m_eat)
			n_times--;
	}
	return (NULL);
}

// int check_died(t_philo *philo)
// {
// 	int i;

// 	i = 0;
// 	while (i < philo->total_ph)
// 	{
// 		pthread_mutex_lock(&philo->mutex_lock);
// 		if (philo->stop == DIED)
// 		{
// 			pthread_mutex_unlock(&philo->mutex_lock);
// 			return (DIED);
// 		}
// 		pthread_mutex_unlock(&philo->mutex_lock);
// 		philo = philo->next;
// 		i++;
// 	}
// 	return (LIFE);
// }

int create_threads(t_philo *philo)
{
	int i;
	pthread_t *threads;

	threads = malloc(sizeof(pthread_t) * philo->total_ph);
	i = 0;
	while (i < philo->total_ph)
	{
		pthread_create(&threads[i], NULL, philosopher, philo);
		if (i % 2 == 0)
			usleep(10);
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

// void lock_all(t_philo *philo)
// {
// 	int i;
// 	i = 0;
// 	t_philo *tmp;
// 	tmp = philo;
// 	while (i < tmp->total_ph)
// 	{
// 		pthread_mutex_lock(&tmp->mutex_lock);
// 		tmp = tmp->next;
// 		i++;
// 	}
// }
// void unlock_all(t_philo *philo)
// {
// 	int i;
// 	i = 0;
// 	t_philo *tmp;
// 	tmp = philo;
// 	while (i < tmp->total_ph)
// 	{
// 		pthread_mutex_unlock(&tmp->mutex_lock);
// 		tmp = tmp->next;
// 		i++;
// 	}
// }
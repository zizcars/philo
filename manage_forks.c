/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:29 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/03 18:36:55 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//remamber to handel the max of thread in your machine

void *philo_function(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	if (philo->n_fork == 1 && philo->next->n_fork == 1)
	{
		philo->next->n_fork -= 1;
		philo->n_fork += 1;
		if (philo->n_fork == 2)
			philo->state = EATING;
	}
	else if (philo->state == EATING)
		philo->state = SLEEPING;
	printf("%d\t%d\n", philo->n_ph, philo->state);
	// sleep(2);
	return (NULL);
}

int create_threads(t_philo *philo)
{
	pthread_t *threads;
	int i;
	int onetime;

	onetime = 1;
	i = 0;
	threads = malloc(sizeof(pthread_t) * (philo->n_ph - 1));
	// philo = philo->next;
	while (onetime || philo->n_ph != 1)
	{
		printf("%d\n",philo->n_ph);
		pthread_create(&threads[i], NULL, philo_function, philo);
		philo = philo->next;
		i++;
		onetime = 0;
	}
	int max;
	max = i;
	i = 0;
	// // philo = philo->next;
	while (i < max)
	{
		// printf("%d\t%d\n", i, philo->state);
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}
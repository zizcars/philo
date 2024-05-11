/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:10:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/11 14:12:28 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int set_numbers(t_philo *philo, int ac, char **av)
{
	philo->total_ph = convert_int(av[1]);
	if (philo->total_ph == ERROR)
		return (ERROR);
	philo->t_die = convert_int(av[2]);
	if (philo->t_die == ERROR)
		return (ERROR);
	philo->t_eat = convert_int(av[3]);
	if (philo->t_eat == ERROR)
		return (ERROR);
	philo->t_sleep = convert_int(av[4]);
	if (philo->t_sleep == ERROR)
		return (ERROR);
	if (ac == 6)
	{
		philo->n_t_m_eat = convert_int(av[5]);
		if (philo->n_t_m_eat == ERROR)
			return (ERROR);
	}
	else
		philo->n_t_m_eat = 0;
	return (GOOD);
}

t_philo *set_philo(int id)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (pthread_mutex_init(&philo->l_fork, NULL) || pthread_mutex_init(&philo->r_fork, NULL) || pthread_mutex_init(&philo->mutex_lock, NULL) )
		return (NULL);
	if (pthread_mutex_init(&philo->mutex_print, NULL) || pthread_mutex_init(&philo->mutex_thread, NULL))
		return (NULL);
	philo->id = id;
	philo->stop = LIFE;
	philo->print = 1;
	return (philo);
}

t_philo *set_default(int ac, char **av)
{
	int id;
	t_philo *first;
	t_philo *tmp;
	t_philo *philo;

	id = 1;
	philo = set_philo(id++);
	if (philo == NULL || set_numbers(philo, ac, av))
		return (NULL);
	first = philo;
	while (id <= philo->total_ph)
	{
		tmp = philo;
		philo = set_philo(id);
		if (philo == NULL || set_numbers(philo, ac, av))
		{
			free_all(first);
			return (NULL);
		}
		tmp->next = philo;
		id++;
	}
	philo->next = first;
	return (first);
}

void free_all(t_philo *philo)
{
	int check;
	t_philo *tmp;

	check = philo->id;
	philo = philo->next;
	while (philo->id != check)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
	free(philo);
	philo = NULL;
}

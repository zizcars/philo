/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:10:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/08 19:42:51 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int set_default(t_philo *philo, int ac, char **av)
{
	philo->total_ph = convert_int(av[1]);
	if (philo->total_ph == -1)
		return (1);
	philo->t_die = convert_int(av[2]);
	if (philo->t_die == -1)
		return (1);
	philo->t_eat = convert_int(av[3]);
	if (philo->t_eat == -1)
		return (1);
	philo->t_sleep = convert_int(av[4]);
	if (philo->t_sleep == -1)
		return (1);
	if (ac == 6)
	{
		philo->n_t_m_eat = convert_int(av[5]);
		if (philo->n_t_m_eat == -1)
			return (1);
	}
	else
		philo->n_t_m_eat = 0;
	return (0);
}

t_philo *create_philo(int id)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (pthread_mutex_init(&philo->l_fork, NULL) || pthread_mutex_init(&philo->r_fork, NULL))
		return (NULL);
	philo->id = id;
	philo->state = THINKING;
	philo->stop = 1;
	return (philo);
}

t_philo *create_table(int ac, char **av)
{
	int id;
	t_philo *tmp;
	t_philo *first;
	t_philo *philo;

	id = 1;
	philo = create_philo(id++);
	if (philo == NULL || set_default(philo, ac, av))
		return (NULL);
	first = philo;
	while (id <= philo->total_ph)
	{
		tmp = philo;
		philo = create_philo(id);
		if (philo == NULL || set_default(philo, ac, av))
		{
			free_all(first);
			return (NULL);
		}
		tmp->next = philo;
		philo->previous = tmp;
		id++;
	}
	philo->next = first;
	first->previous = philo;
	return (first);
}

void free_all(t_philo *table)
{
	int check;
	t_philo *tmp;

	check = table->id;
	table = table->next;
	while (table->id != check)
	{
		tmp = table->next;
		free(table);
		table = tmp;
	}
	free(table);
	table = NULL;
}

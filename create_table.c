/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:10:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/03 16:20:59 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int set_default(t_info *philo_info, int ac, char **av)
{
	philo_info->total_ph = convert_int(av[1]);
	if (philo_info->total_ph == -1)
		return (1);
	philo_info->t_die = convert_int(av[2]);
	if (philo_info->t_die == -1)
		return (1);
	philo_info->t_eat = convert_int(av[3]);
	if (philo_info->t_eat == -1)
		return (1);
	philo_info->t_sleep = convert_int(av[4]);
	if (philo_info->t_sleep == -1)
		return (1);
	if (ac == 6)
	{
		philo_info->n_t_m_eat = convert_int(av[5]);
		if (philo_info->n_t_m_eat == -1)
			return (1);
	}
	else
		philo_info->n_t_m_eat = 0;
	return (0);
}

t_philo *create_philo(t_info philo_info, int i)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	philo->n_ph = i;
	philo->n_fork = 1;
	philo->state = THINKING;
	philo->philo_info = philo_info;
	philo->next = NULL;
	// philo->previous = NULL;
	return (philo);
}

t_philo *create_table(t_info philo_info)
{
	int i;
	t_philo *tmp;
	t_philo *first;
	t_philo *table;
	int one_time;

	one_time = 1;
	i = philo_info.total_ph;
	table = NULL;
	while (i)
	{
		tmp = table;
		table = create_philo(philo_info, i);
		if (one_time)
		{
			one_time = 0;
			first = table;
		}
		table->next = tmp;
		i--;
	}
	first->next = table;
	return (table);
}

void free_all(t_philo *table)
{
	int check;
	t_philo *tmp;

	check = table->n_ph;
	table = table->next;
	while (table->n_ph != check)
	{
		tmp = table->next;
		free(table);
		table = tmp;
	}
	free(table);
	table = NULL;
}

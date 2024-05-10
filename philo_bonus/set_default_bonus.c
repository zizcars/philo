/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:10:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/10 20:23:43 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int get_numbers(t_philo *philo, int ac, char **av)
{
	philo->stop = LIFE;
	philo->print_message = 1;
	philo->id = 1;
	philo->total_ph = convert_int(av[1]);
	if (philo->total_ph == -1)
		return (ERROR);
	philo->t_die = convert_int(av[2]);
	if (philo->t_die == -1)
		return (ERROR);
	philo->t_eat = convert_int(av[3]);
	if (philo->t_eat == -1)
		return (ERROR);
	philo->t_sleep = convert_int(av[4]);
	if (philo->t_sleep == -1)
		return (ERROR);
	if (ac == 6)
	{
		philo->n_t_m_eat = convert_int(av[5]);
		if (philo->n_t_m_eat == -1)
			return (ERROR);
	}
	else
		philo->n_t_m_eat = 0;
	return (GOOD);
}

int default_info(t_philo *philo, int ac, char **av)
{
	int number_eaters;

	if (get_numbers(philo , ac, av) == ERROR)
		return (ERROR);
	if (philo->total_ph % 2 == 0)
		number_eaters = philo->total_ph / 2;
	else
		number_eaters = (philo->total_ph - 1) / 2;
	philo->semaphore = sem_open("forks", O_CREAT, 0644, number_eaters);
	if (philo->semaphore == SEM_FAILED)
		return (ERROR);
	return(GOOD);
}

// void children(int ac, char **av)
// {
// 	id = 1;
// 	philo = create_philo(id++);
// 	if (philo == NULL || set_default(philo, ac, av))
// 		return (NULL);
// }


// void free_all(t_philo *table)
// {
// 	int check;
// 	t_philo *tmp;

// 	check = table->id;
// 	table = table->next;
// 	while (table->id != check)
// 	{
// 		tmp = table->next;
// 		free(table);
// 		table = tmp;
// 	}
// 	free(table);
// 	table = NULL;
// }

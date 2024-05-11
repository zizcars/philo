/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:10:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/11 12:06:59 by achakkaf         ###   ########.fr       */
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

// int default_info(t_philo *philo, int ac, char **av)
// {
// 	int number_eaters;

// 	if (get_numbers(philo , ac, av) == ERROR)
// 		return (ERROR);
// 	if (philo->total_ph % 2 == 0)
// 		number_eaters = philo->total_ph / 2;
// 	else
// 		number_eaters = (philo->total_ph - 1) / 2;
// 	philo->semaphore = sem_open("forks", O_CREAT, 0644, philo->total_ph);
// 	if (philo->semaphore == SEM_FAILED)
// 		return (ERROR);
// 	philo->lock = sem_open("lock", O_CREAT, 0644, 1);
// 	if (philo->lock == SEM_FAILED)
// 		return (ERROR);
// 	philo->mutex = sem_open("mutex", O_CREAT, 0644, number_eaters);
// 	if (philo->mutex == SEM_FAILED)
// 		return (ERROR);
// 	return(GOOD);
// }
int default_info(t_philo *philo, int ac, char **av)
{
    int number_forks;

    if (get_numbers(philo, ac, av) == ERROR)
        return (ERROR);
    if (philo->total_ph % 2 == 0)
        number_forks = philo->total_ph / 2;
    else
        number_forks = (philo->total_ph - 1) / 2;
    philo->semaphore = sem_open("forks", O_EXCL | O_CREAT, 0644, number_forks);
    if (philo->semaphore == SEM_FAILED)
    {
        sem_unlink("forks");
        return (ERROR);
    }
    philo->lock = sem_open("lock", O_EXCL | O_CREAT, 0644, 1);
    if (philo->lock == SEM_FAILED)
    {
        sem_unlink("lock");
        return (ERROR);
    }
    philo->mutex = sem_open("mutex", O_EXCL | O_CREAT, 0644, number_forks);
    if (philo->mutex == SEM_FAILED)
    {
        sem_unlink("mutex");
        return (ERROR);
    }
    return (GOOD);
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

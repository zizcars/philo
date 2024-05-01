/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/01 12:37:49 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pholi.h"

int set_default(t_philo_info *philo_info, int ac, char **av)
{
	philo_info->n_ph = convert_int(av[1]);
	if (philo_info->n_ph.error)
		return (1);
	philo_info->t_die = convert_int(av[2]);
	if (philo_info->t_die.error)
		return (1);
	philo_info->t_eat = convert_int(av[3]);
	if (philo_info->t_eat.error)
		return (1);
	philo_info->t_sleep = convert_int(av[4]);
	if (philo_info->t_sleep.error)
		return (1);
	if (ac == 6)
		philo_info->n_t_m_eat = convert_int(av[5]);
	else
	{
		philo_info->n_t_m_eat.number = -1;
		philo_info->n_t_m_eat.error = 0;
	}
	philo_info->n_fork = philo_info->n_ph;
	return (0);
}

int main(int ac, char **av)
{
	t_philo_info philo_info;

	if (ac < 5 || ac > 6)
	{
		write(2, "Error\n", 7);
		return (1);
	}
	if (set_default(&philo_info, ac, av))
	{
		write(2, "Error\n", 7);
		return (1);
	}
}

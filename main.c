/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/03 18:34:05 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void leaks()
// {
// 	system("leaks philo");	
// }

int main(int ac, char **av)
{
	t_info philo_info;
	t_philo *philo;

	// atexit(leaks);
	if (ac < 5 || ac > 6)
	{
		write(2, "Error1\n", 7);
		return (1);
	}
	if (set_default(&philo_info, ac, av))
	{
		write(2, "Error2\n", 7);
		return (1);
	}
	philo = create_table(philo_info);
	create_threads(philo);
	// printf("%d\t%d\n", philo->state, philo->n_ph);
	free_all(philo);
}

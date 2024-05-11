/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/11 18:43:13 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void leaks()
// {
// 	system("leaks philo");
// }

int main(int ac, char **av)
{
	t_philo *philo;

	// atexit(leaks);
	if (ac < 5 || ac > 6)
	{
		write(2, "ERROR: Incorrect number of arguments\n", 38);
		return (1);
	}
	if ((philo = set_default(ac, av)) == NULL)
	{
		write(2, "ERROR: Failed to initialize philosophers\n", 42);
		return (1);
	}
	create_threads(philo);
	free_all(philo);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/07 19:10:19 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void leaks()
{
	system("leaks philo");	
}

int main(int ac, char **av)
{
	t_info philo_info;
	t_philo *philo;

	atexit(leaks);
	if (ac < 5 || ac > 6)
	{
		write(2, "\e[31mError1\n\e[0m", 17);
		return (1);
	}
	if (set_default(&philo_info, ac, av))
	{
		write(2, "Error2\n", 7);
		return (1);
	}
	philo = create_table(philo_info);
	// int i;
	// i = 0;
	// while(i < philo_info.total_ph)
	// {
	// 	printf("%d\t%d\t%d\n",philo->previous->n_ph, philo->n_ph, philo->next->n_ph);
	// 	philo = philo->next;
	// 	i++;
	// }
	// create_threads(philo);
	// printf("%d\t%d\n", philo->state, philo->n_ph);
	free_all(philo);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/08 17:03:48 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void leaks()
{
	system("leaks philo");	
}

int main(int ac, char **av)
{
	t_philo *philo;

	// atexit(leaks);
	if (ac < 5 || ac > 6)
	{
		write(2, "\e[31mError1\n\e[0m", 17);
		return (1);
	}
	// if (set_default(&philo, ac, av))
	// {
	// 	
	// }
	if ((philo = create_table(ac, av)) == NULL)
	{
		write(2, "Error2\n", 7);
		return (1);
	};
	// int i;
	// i = 0;
	// while (i < philo->total_ph)
	// {
	// 	// printf("%d\t%d\t%d\n\n",philo->previous->id, philo->id, philo->next->id);
	// 	printf("%d\t%d\t%d\t%d\t%d\t%d\n",philo->id, philo->state, philo->t_die, philo->t_eat, philo->t_sleep, philo->total_ph);
	// 	philo = philo->next;
	// 	i++;
	// }
	create_threads(philo);
	// printf("%d\t%d\n", philo->state, philo->n_ph);
	free_all(philo);
}


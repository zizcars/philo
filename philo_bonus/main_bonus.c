/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/10 20:24:04 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void leaks()
// {
// 	system("leaks philo");
// }

int main(int ac, char **av)
{
	t_philo philo;
	// atexit(leaks);
	if (ac < 5 || ac > 6)
	{
		write(2, RED"ERROR1\n", 13);
		return (1);
	}
	if (default_info(&philo, ac, av) == ERROR)
	{
		write(2, RED"ERROR2\n", 13);
		return (1);
	}
	while(philo.id < philo.total_ph)
	{
		
		philo.id++;
	}
	printf("%d %d\n",philo.print_message, philo.stop);
}

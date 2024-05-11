/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/11 11:55:40 by achakkaf         ###   ########.fr       */
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
	sem_unlink("forks");
	sem_unlink("lock");
	sem_unlink("mutex");
	if (ac < 5 || ac > 6)
	{
		write(2, "ERROR: Incorrect number of arguments\n", 37);
		return (1);
	}
	if (default_info(&philo, ac, av) == ERROR)
	{
		write(2, "ERROR: Failed to initialize philosophers\n", 42);
		return (1);
	}
	if (create_children(&philo) == ERROR)
    {
        write(2, "ERROR: Failed to create philosopher processes\n", 47);
        return (1);
    }
	while (waitpid(-1, NULL, 0 ) > 0);
	// printf("%d %d\n",philo.print_message, philo.stop);
}

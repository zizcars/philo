/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/10 12:48:49 by achakkaf         ###   ########.fr       */
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

	atexit(leaks);
	if (ac < 5 || ac > 6)
	{
		write(2, "\e[31mError1\n\e[0m", 17);
		return (1);
	}
	if ((philo = create_table(ac, av)) == NULL)
	{
		write(2, "Error2\n", 7);
		return (1);
	};
	create_threads(philo);
	free_all(philo);
}

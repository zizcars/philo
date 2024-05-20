/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/20 16:32:30 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void ft_error(char *error_massege)
{
	int len;

	len = 0;
	while (error_massege[len])
		len++;
	write(STDERR, error_massege, len);
}

void leaks(void)
{
	system("leaks philo_bonus");
}

int main(int ac, char **av)
{
	t_data data;

	// atexit(leaks);
	if (ac < 5 || ac > 6)
	{
		ft_error("Error: incorrect number of arguments\n");
		return (1);
	}
	if (set_init(&data, ac, av) == ERROR)
		return (1);
	add_threads(&data);
	// {
	// 	clean_all(&data);
	// 	return (1);
	// }
	// clean_all(&data);
}

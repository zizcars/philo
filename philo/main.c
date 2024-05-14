/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/13 15:23:38 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_error(char *error_massege)
{
	int len;

	len = 0;
	while (error_massege[len])
		len++;
	write(STDERR, error_massege, len);
}

int main(int ac, char **av)
{
	t_data data;

	if (ac < 5 || ac > 6)
	{
		ft_error("Error: incorrect number of arguments\n");
		return (1);
	}
	if (set_init(&data, ac, av) == ERROR)
		return (1);
	add_threads(&data);
	// printf("%d\n", data.n_t_m_eat);
	// int i; 
	// i = 0;
	// while(i < data.philos[0].data->total_ph)
	// {
	// 	printf("%d: %d\n", data.philos[i].id, i );
	// 	i++;
	// }
}
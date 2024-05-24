/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/24 15:39:54 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_error(char *error_massege)
{
	int	len;

	len = 0;
	while (error_massege[len])
		len++;
	write(STDERR_FILENO, error_massege, len);
}

void	clean(t_data *data)
{
	free(data->pid);
	data->pid = NULL;
	free(data->philos);
	data->philos = NULL;
	sem_close(data->forks);
	sem_unlink("forks");
	sem_close(data->lock);
	sem_unlink("lock");
	sem_close(data->print);
	sem_unlink("print");
	sem_close(data->sem_fast);
	sem_unlink("sem_fast");
	sem_close(data->sem_start);
	sem_unlink("sem_start");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		ft_error("Error: incorrect number of arguments\n");
		return (EXIT_FAILURE);
	}
	set_numbers(&data, ac, av);
	set_philo_info(&data);
	creat_philos(&data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tooles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:39:09 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/20 15:44:31 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mssleep(int time_to_sleep, t_philo *philo)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_to_sleep)
	{
		usleep(100);
		if (check_death(philo) == DIED)
			return ;
	}
}

long	get_time(void)
{
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL))
		return (ERROR);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tooles_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:36:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/24 15:40:58 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	skip_space(char **str)
{
	if (str == NULL || *str == NULL)
		return ;
	while (**str && (**str == ' ' || **str == '	'))
		(*str)++;
}

int	convert_int(char *str)
{
	int	number;

	number = 0;
	skip_space(&str);
	if (str == NULL || *str == '-' || *str == '\0')
	{
		ft_error("Error: Incorrect number\n");
		exit(EXIT_FAILURE);
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + *str - 48;
		str++;
	}
	skip_space(&str);
	if (*str != '\0' || number == 0)
	{
		ft_error("Error: Incorrect number\n");
		exit(EXIT_FAILURE);
	}
	return (number);
}

long	get_time(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

void	print_message(char *message, t_philo *philo, long print_time)
{
	sem_wait(philo->data->print);
	printf("%ld %d %s\n", print_time - philo->data->start_t, philo->id, message);
	sem_post(philo->data->print);
}

void	mssleep(int time_ms)
{
	long	start;

	start = get_time();
	while (get_time() - start < time_ms)
		usleep(85);
}

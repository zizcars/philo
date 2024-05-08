/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tooles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:36:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/08 16:57:15 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void skip_space(char **str)
{
	if (str == NULL || *str == NULL)
		return ;
	while (**str && (**str == ' ' || **str == '	'))
		(*str)++;
}

int convert_int(char *str)
{
	int	number;

	number = 0;
	skip_space(&str);
	if (str == NULL || *str == '-' || *str == '\0')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + *str - 48;
		str++;
	}
	skip_space(&str);
	if (*str != '\0')
		return (-1);
	if (number < 2)
		return (-1);
	return (number);
}


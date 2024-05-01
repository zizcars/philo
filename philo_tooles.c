/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tooles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:36:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/01 14:58:29 by achakkaf         ###   ########.fr       */
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

t_number convert_int(char *str)
{
	t_number	n_info;

	n_info.number = 0;
	skip_space(&str);
	if (str == NULL || *str == '-' || *str == '\0')
	{
		n_info.error = 1;
		return (n_info);
	}
	else if (*str == '+')
		str++;
	while (*str > '0' && *str < '9')
	{
		n_info.number = n_info.number * 10 + *str - 48;
		str++;
	}
	skip_space(&str);
	if (*str != '\0')
	{
		n_info.error = 1;
		return (n_info);
	}
	if (n_info.number == 0)
		n_info.error = 1;
	return (n_info);
}

// int check_invalid(t_philo_info *philo_info)
// {
	
// }
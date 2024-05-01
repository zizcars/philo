/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:38 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/01 16:47:28 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
/// @brief take a number and error status
typedef struct s_number
{
	long number;
	int error;
} t_number;

/// @brief take all info about philosophers
typedef struct s_philo_info
{
	t_number n_ph;
	t_number n_fork;
	t_number t_die;
	t_number t_eat;
	t_number t_sleep;
	t_number n_t_m_eat;
}   t_philo_info;


/// @brief convert from char * to a number and if the number is invalid set error variable to 1
/// @param str the number in form of char *
/// @return number and error status
t_number convert_int(char *str);

/// @brief this function set t_philo_info struct to it default value
/// @param philo_info adress of struct
/// @param ac number of arguments 
/// @param av arguments
/// @return status of error 1 for error and 0 for normal
int set_default(t_philo_info *philo_info, int ac, char **av);


#endif
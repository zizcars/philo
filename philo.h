/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:38 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/07 15:14:39 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

typedef enum s_state
{
	THINKING = 1,
	EATING = 2,
	SLEEPING = 3,
} t_state; 
typedef struct s_info
{
	int total_ph;
	long t_die;
	long t_eat;
	long t_sleep;
	int n_t_m_eat;
} t_info;

/// @brief take all info about philosophers
typedef struct s_philo
{
	int n_ph;
	int n_fork;
	t_info philo_info;
	t_state state;
	pthread_mutex_t lock;
	struct s_philo *next;
	struct s_philo *previous;
} t_philo;

/// @brief convert from char * to a number and if the number is invalid set error variable to 1
/// @param str the number in form of char *
/// @return number or -1 for an error
long convert_int(char *str);

/// @brief this function set t_philo_info struct to it default value
/// @param philo_info adress of struct
/// @param ac number of arguments
/// @param av arguments
/// @return status of error 1 for error and 0 for normal
int set_default(t_info *philo_info, int ac, char **av);


/// @brief fill all the information every philo need
/// @param philo_info inforamation came from set_default
/// @param philo_n philosopher number
/// @return the address of philo 
t_philo *create_philo(t_info philo_info, int philo_n);

/// @brief create a circuler linked list with philo struct
/// @param philo_info 
/// @return the head of linked list
t_philo *create_table(t_info philo_info);

/// @brief free all the lists
/// @param table the head of linked list
void free_all(t_philo *table);

/// @brief create thread for every philo
/// @param philo the head of circuler linked list
/// @return state of the function 0 ok -1 error
int create_threads(t_philo *philo);

#endif
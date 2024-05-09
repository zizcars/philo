/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:38 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/09 17:03:46 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define DIED -1
#define LIFE 0
// typedef enum s_state
// {
// 	THINKING = 1,
// 	EATING = 2,
// 	SLEEPING = 3,
// } t_state; 

/// @brief take all info about philosophers
typedef struct s_philo
{
	int id;
	pthread_mutex_t print_mutex;
	int print_message;
	int stop;
	pthread_mutex_t mutex_lock;
	// t_state state;
	int total_ph;
	int t_die;
	int t_eat;
	int t_sleep;
	int n_t_m_eat;
	struct timeval start_t;
	struct timeval end_t;
	struct timeval start;
	pthread_mutex_t l_fork;
	pthread_mutex_t r_fork;
	struct s_philo *next;
	// struct s_philo *previous;
} t_philo;

/// @brief convert from char * to a number and if the number is invalid set error variable to 1
/// @param str the number in form of char *
/// @return number or -1 for an error
int convert_int(char *str);

/// @brief this function set t_philo_info struct to it default value
/// @param philo_info adress of struct
/// @param ac number of arguments
/// @param av arguments
/// @return status of error 1 for error and 0 for normal
int set_default(t_philo *philo_info, int ac, char **av);


/// @brief fill all the information every philo need
/// @param philo_info inforamation came from set_default
/// @param philo_n philosopher number
/// @return the address of philo 
t_philo *create_philo(int id);

/// @brief create a circuler linked list with philo struct
/// @param philo_info 
/// @return the head of linked list
t_philo *create_table(int ac, char **av);

/// @brief free all the lists
/// @param table the head of linked list
void free_all(t_philo *table);

/// @brief create thread for every philo
/// @param philo the head of circuler linked list
/// @return state of the function 0 ok -1 error
int create_threads(t_philo *philo);


int get_time(struct timeval start_t);
int eating(t_philo *philo, struct timeval start);
// int check_died(t_philo *philo);
void *philosopher(void *arg);
int create_threads(t_philo *philo);


int ft_sleep(t_philo *philo, int time_us);
int died(t_philo *philo);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:38 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/11 16:23:19 by achakkaf         ###   ########.fr       */
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
#define ERROR -1
#define GOOD 0


/// @brief take all info about philosophers
typedef struct s_philo
{
	int id;
	int print;
	int stop;
	int total_ph;
	int t_die;
	int t_eat;
	int t_sleep;
	int n_t_m_eat;
	struct timeval start_t;
	struct timeval start;
	struct timeval end_t;
	struct timeval tmp_t;
	pthread_mutex_t r_fork;
	pthread_mutex_t l_fork;
	pthread_mutex_t mutex_print;
	pthread_mutex_t mutex_lock;
	pthread_mutex_t mutex_thread;
	struct s_philo *next;
} t_philo;

/// @brief convert from string to int positive
/// @param str string
/// @return number or -1 for error
int convert_int(char *str);

/// @brief change argments from string to numbers
/// @param philo philo struct
/// @param ac number of argument
/// @param av argments
/// @return state of function 0 is good or -1 for and error
int set_numbers(t_philo *philo, int ac, char **av);

/// @brief set mutex, id, stop, print
/// @param id number of philosopher
/// @return philosopher struct
t_philo *set_philo(int id);

/// @brief set linked list of philosophers to its default values
/// @param ac number of arguments
/// @param av arguments
/// @return head of the linked list
t_philo *set_default(int ac, char **av);

/// @brief free all linked list
/// @param philo a philosopher from the linked list
void free_all(t_philo *philo);

int create_threads(t_philo *philo);
int eating(t_philo *philo, struct timeval start);
int died(t_philo *philo);
void lock_all(t_philo *philo);
void unlock_all(t_philo *philo);
int ft_sleep(t_philo *philo, int time_ms);
int get_time(struct timeval start_t);
#endif
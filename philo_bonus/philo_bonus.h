/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:38 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/11 11:33:52 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define DIED -1
#define LIFE 0
#define GOOD 0
#define ERROR -1
#define RED "\e[31m"

/// @brief take all info about philosophers
typedef struct s_philo
{
	int id;
	int total_ph;
	int t_die;
	int t_eat;
	int t_sleep;
	int n_t_m_eat;
	struct timeval start;
	struct timeval start_t;
	struct timeval end_t;
	int print_message;
	int stop;
	sem_t *semaphore;
	sem_t *mutex;
	sem_t *lock;
} t_philo;

int convert_int(char *str);

int get_numbers(t_philo *philo_info, int ac, char **av);

int default_info(t_philo *philo, int ac, char **av);

int create_children(t_philo *philo);

int died(t_philo *philo);

int eating(t_philo *philo, struct timeval start);

int ft_sleep(t_philo *philo, int time_ms);

int get_time(struct timeval start_t);




// t_philo *create_table(int ac, char **av);
/// @brief free all the lists
/// @param table the head of linked list
// void free_all(t_philo *table);
/// @brief create thread for every philo
/// @param philo the head of circuler linked list
/// @return state of the function 0 ok -1 error
// int create_threads(t_philo *philo);
// int get_time(struct timeval start_t);
// int eating(t_philo *philo, struct timeval start);
// int check_died(t_philo *philo);
// void *philosopher(void *arg);
// int create_threads(t_philo *philo);
// int ft_sleep(t_philo *philo, int time_us);
// int died(t_philo *philo);

#endif
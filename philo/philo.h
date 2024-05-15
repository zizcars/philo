/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:38 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/15 11:56:29 by achakkaf         ###   ########.fr       */
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
#define EATING 2
#define NOT_EATING 0

#define STDERR 2

typedef struct s_philo
{
	int id;
	long last_meal;
	long start;
	int is_eating;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t write;
	struct s_data *data;
} t_philo;

typedef struct s_data
{
	int total_ph;
	int t_die;
	int t_eat;
	int t_sleep;
	int n_t_m_eat;
	int dead;
	int stop;
	long start_t;
	t_philo *philos;
	int n_times;
	pthread_mutex_t lock_n_times;
	pthread_mutex_t **forks;
	pthread_mutex_t lock;
}	t_data;

/*-----------------set_default-----------*/
int set_default(t_data *data, int ac, char **av);
int data_alloc(t_data *data);
int set_id_forks(t_data *data);
int set_init(t_data *data, int ac, char **av);

/*-----------------convert_int-----------*/
int convert_int(char *str);

/*-----------------main-----------*/
void ft_error(char *error_massege);
int check_stop(t_data *data);
/*-----------------thread_managment-----------*/
long get_time(void);
int add_threads(t_data *data);
void *philosopher(void *arg);
int ft_sleep(int time_ms, t_philo *philo);
void print_message(char *message, t_philo *philo);
int join_free(t_data *data, pthread_t *threads);

/*-----------------routine-----------*/
void routine(t_philo *philo);
void take_forks(t_philo *philo);
void put_forks(t_philo *philo);
int check_death(t_philo *philo);
// void *died(void *arg);
void *monitor(void *arg);
int check_n_times(t_data *data);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:38 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/14 14:57:00 by achakkaf         ###   ########.fr       */
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
	// int n_t_m_eat;
	long last_meal;
	// struct timeval end_t;
	long start;
	// int print_message;
	// int stop;
	int is_eating;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	// pthread_mutex_t mutex_lock;
	pthread_mutex_t write;
	// pthread_mutex_t print_mutex;
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
	long start_t;
	t_philo *philos;
	// struct timeval start;
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

/*-----------------thread_managment-----------*/
long get_time(void);
int add_threads(t_data *data);
void *philosopher(void *arg);
int ft_sleep(int time_ms, t_philo *philo);
void print_message(char *message, t_philo *philo);

/*-----------------routine-----------*/
void routine(t_philo *philo);
void take_forks(t_philo *philo);
void put_forks(t_philo *philo);
int check_death(t_philo *philo);
// void *died(void *arg);
void *monitor(void *arg);

#endif
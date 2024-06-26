/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:38 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/22 17:06:14 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <semaphore.h>
#include <stdlib.h>

#define DIED -1
#define LIFE 0
#define ERROR -1
#define GOOD 0
#define EATING 2
#define NOT_EATING 0

#define STDERR 2


typedef enum s_state
{
	go_eat = 1,
	go_sleep = 2
} t_state;
typedef struct s_philo
{
	int id;
	long last_meal;
	int n_times_eat;
	t_state state;
	struct s_data *data;
	sem_t *sem_last_meal;
	sem_t *n_times;
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
	int n_times;
	sem_t *forks;
	sem_t *lock;
	sem_t *print;
	sem_t *start_sem;
	sem_t *sem_fast;
	sem_t *sem_start;
	pid_t *pid;
}	t_data;

/*-----------------set_default-----------*/
int set_default(t_data *data, int ac, char **av);
int data_alloc(t_data *data);
int set_id_forks(t_data *data);
int set_init(t_data *data, int ac, char **av);
long check_last_meal(t_philo *philo, int update);
/*-----------------convert_int-----------*/
int convert_int(char *str);

/*-----------------main-----------*/
void ft_error(char *error_massege);
// int check_stop(t_data *data);
/*-----------------thread_managment-----------*/
long get_time(void);
void add_threads(t_data *data);
void philosopher(t_philo *philo);
void mssleep(int time_ms);
void sleeping(t_philo *philo);
void print_message(char *message, t_philo *philo, long print_time);
// void join_free(t_data *data ,pid_t *pid);

/*-----------------routine-----------*/
void eating(t_philo *philo);
void take_forks(t_philo *philo);
void put_forks(t_philo *philo);
void check_death(t_philo *philo);
// void *died(void *arg);
// int monitor(t_data *data);
// int check_n_times(t_data *data);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:38 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/24 15:37:10 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdlib.h>

# define CHILD_MAX 200

# define DIED -1
# define LIFE 0
# define ERROR -1
# define GOOD 0

typedef enum s_state
{
	go_eat = 1,
	go_sleep = 2
}	t_state;
typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				n_times_eat;
	t_state			state;
	struct s_data	*data;
	sem_t			*sem_last_meal;
	sem_t			*n_times;
}	t_philo;

typedef struct s_data
{
	int		total_ph;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_t_m_eat;
	int		n_times;
	int		dead;
	long	start_t;
	pid_t	*pid;
	sem_t	*forks;
	sem_t	*lock;
	sem_t	*print;
	sem_t	*sem_fast;
	sem_t	*sem_start;
	t_philo	*philos;
}	t_data;

void	set_numbers(t_data *data, int ac, char **av);
void	creat_sem(sem_t **sem, char *sem_name, int n);
void	set_philo_info(t_data *data);
void	clean(t_data *data);
void	*death_checker(void *arg);
void	creat_philos(t_data *data);
int		convert_int(char *str);
long	get_time(void);
void	mssleep(int time_ms);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
long	check_last_meal(t_philo *philo, int update);
void	ft_error(char *error_massege);
void	print_message(char *message, t_philo *philo, long print_time);

#endif

// #include <stdio.h>
// #include <unistd.h>
// #include <semaphore.h>
// #include <fcntl.h>
// #include <sys/wait.h>
// int main()
// {
//     sem_t *semaphore = sem_open("abdo", O_CREAT, 0644, 1);
//     pid_t pid[2];
//     if (semaphore == SEM_FAILED)
//     {
//         perror("sem_open/semaphore");
//         return 1;
//     }

//     for (int i = 0; i < 2; i++)
//     {
//         pid[i] = fork();
//         if (pid[i] < 0)
//         {
//             perror("fork");
//             return 1;
//         }
//         else if (pid[i] == 0)
//         {
//             sem_wait(semaphore);
//             printf("Child process %d\n", i);
//             sem_post(semaphore);
//             sleep(4);
//             // return 0;
//         }
//     }
//     while (waitpid(-1, NULL, 0) > 0);
//     sem_close(semaphore);
//     sem_unlink("abdo");

//     return 0;
// }

#include "philo/philo.h"
long get_time(void);
int ft_sleep(int time_ms)
{
	long start, end;
	long elapsed;

	while (time_ms > 0)
	{
        start = get_time();
		usleep(1000);
		end = get_time();
		elapsed = end - start;
		time_ms -= elapsed;
	}
	return (LIFE);
}
long get_time(void)
{
	struct timeval time_now;

	if (gettimeofday(&time_now, NULL))
		return (ERROR);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

int main()
{
	long start, end;
    start = get_time();
    ft_sleep(1000);
    printf("%ld\n", get_time() - start);
}
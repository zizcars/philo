#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
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

long get_time(void)
{
	struct timeval time_now;

	if (gettimeofday(&time_now, NULL))
		return (0);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

void mssleep(int time_ms)
{
	long start, end;
	long elapsed;
	long sleeping_time;

	
	sleeping_time = 7 * (time_ms / 8) * 1000;
    start = get_time();
	usleep(sleeping_time);
	sleeping_time = time_ms - (sleeping_time / 1000 );
	while (sleeping_time > 0)
	{
		start = get_time();
		usleep(1000);
		end = get_time();
		elapsed = end - start;
		sleeping_time -= elapsed;
	}
}
void ft_sleep(int time_ms)
{
	long start, end;
	long elapsed;

	start = get_time();
    usleep(7 * (time_ms / 8) * 1000);
	end = get_time();
    time_ms = time_ms - (end - start);
	while (time_ms > 0)
	{
		start = get_time();
		usleep(100);
		// if (check_death(philo) == DIED)
		// 	return (DIED);
		end = get_time();
		elapsed = end - start;
		time_ms -= elapsed;
	}
	// return (0);
}
void tf_sleep(int time_to_sleep)
{
    size_t  start;

    start = get_time();
    while ((get_time() - start) < time_to_sleep)
        usleep (100);  
}
int main()
{
    long start = get_time();
    mssleep(3000);
    printf("%ld\n", get_time() - start );
    start = get_time();
    ft_sleep(3000);
    printf("%ld\n", get_time() - start );
    start = get_time();
    tf_sleep(3000);
    printf("%ld\n", get_time() - start );
}

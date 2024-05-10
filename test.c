#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    sem_t *semaphore = sem_open("abdo", O_CREAT, 0644, 1);
    pid_t pid[2];
    if (semaphore == SEM_FAILED)
    {
        perror("sem_open/semaphore");
        return 1;
    }

    for (int i = 0; i < 2; i++)
    {
        pid[i] = fork();
        if (pid[i] < 0)
        {
            perror("fork");
            return 1;
        }
        else if (pid[i] == 0)
        {

            sem_wait(semaphore);
            printf("Child process %d\n", i);
            sem_post(semaphore);
            sleep(4);
            // return 0;
        }
    }
    while (waitpid(-1, NULL, 0) > 0)
        ;
    sem_close(semaphore);
    sem_unlink("abdo");

    return 0;
}
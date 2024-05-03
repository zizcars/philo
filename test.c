
#include "philo.h"

void *think(void *arg);
void *eat(void *arg);
void *sleep_(void *arg);

void *eat(void *arg)
{
	int a = *(int *)arg;
	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL);
	long time = 0;
	while (time < 100)
	{
		printf("I am eating %d\n", a);
		gettimeofday(&end_time, NULL);
		time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
		if (time % 10 > 5)
			printf("%ld\n", time);
	}
	sleep_(&a);
	return NULL;
}

void *sleep_(void *arg)
{
	int a = *(int *)arg;
	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL);
	long time = 0;
	while (time < 100)
	{
		printf("I am sleeping %d\n", a);
		gettimeofday(&end_time, NULL);
		time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
		if (time % 10 > 5)
			printf("%ld\n", time);
	}
	think(&a);
	return NULL;
}

void *think(void *arg)
{
	int a = *(int *)arg;
	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL);
	long time = 0;
	while (time < 100)
	{
		printf("I am thinking %d\n", a);
		gettimeofday(&end_time, NULL);
		time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
		if (time >= 30)
			eat(&a);
		if (time % 10 > 5)
			printf("%ld\n", time);
	}
	printf("deid!!!\n");
	return NULL;
}

void leaks()
{
	system("leaks a.out");
}

void *thread_2(void *arg);
void *thread_1(void *arg)
{
	// sleep(2);
	printf("done sleeping\n");
	int *r;
	r = malloc(sizeof(int));
	*r = 848;
	// r = 889;
	return ((void *)r);
}
void *thread_2(void *arg)
{
	sleep(2);
	printf("start thinking\n");
	return (NULL);
}

int main()
{
	pthread_t thread1;
	pthread_t thread2;
	// time_t start_time, end_time;
	atexit(leaks);
	int one, two;
	int *r;

	one = 1;
	two = 2;
	if (pthread_create(&thread1, NULL, thread_1, NULL) != 0)
	{
		write(2, "pthread_create", 14);
		return 1;
	}
	if (pthread_create(&thread2, NULL, thread_2, NULL) != 0)
	{
		write(2, "pthread_create", 14);
		return 1;
	}
	if (pthread_join(thread1, (void **)&r) != 0)
	{
		write(2, "pthread_detach", 14);
		return 1;
	}
	if (pthread_join(thread2, NULL) != 0)
	{
		write(2, "pthread_detach", 14);
		return 1;
	}
	printf("%d\n",*r);
	free(r);
	return 0;
}


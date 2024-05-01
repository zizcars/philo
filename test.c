
#include "philo.h"

void *thread_function(void *arg)
{
	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL);
	long time;
		// printf("Thread function: received argument\n");
	int i = 1;
	while (i)
	{
		gettimeofday(&end_time, NULL);
		time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
		printf("%ld\n", time);
		if (time >= 30)
			break;
	}
	return NULL;
}

void leaks()
{
	system("leaks a.out");
}
int main()
{
	pthread_t thread1;
	// time_t start_time, end_time;
	atexit(leaks);
	if (pthread_create(&thread1, NULL, thread_function, NULL) != 0)
	{
		write(2, "pthread_create", 14);
		return 1;
	}

	if (pthread_join(thread1, NULL) != 0)
	{
		write(2, "pthread_detach", 14);
		return 1;
	}
	// long time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
	// printf("%s\n", e);
	return 0;
}

// #include <stdio.h>
// #include <sys/time.h>
// int main() {
//     struct timeval start_time, end_time;
// // Get the start time
// gettimeofday(&start_time, NULL);

// // int i;
// // i = 0;
// // while(i < 50000)
// // 	printf("sdf%d\n", i++);

//     // Your program's code here...
// // Get the end time
// gettimeofday(&end_time, NULL);

//     // Calculate the elapsed time in microseconds
// long elapsed_time_us = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);

//     printf("Program execution time: %ld microseconds\n", elapsed_time_us);

//     return 0;
// }

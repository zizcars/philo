#include "philo.h"

int main()
{
    struct timeval start_time;
    struct timeval end_time;

   gettimeofday(&start_time, NULL);
    int i = 0;
    usleep(1000 * 50);
    gettimeofday(&end_time,NULL);
    long time_;

    time_ = ((end_time.tv_sec - start_time.tv_sec) * 1000) + (end_time.tv_usec - start_time.tv_usec) / 1000;
    printf("%ld\n", time_);
}
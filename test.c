
#include "pholi.h"

void *thread_function(void *arg) {
	printf("Thread function: received argument\n");
	return NULL;
}

int main() {
	pthread_t my_thread;

	if (pthread_create(&my_thread, NULL, thread_function, NULL) != 0) {
		write(2, "pthread_create", 14);
		return 1;
	}

	if (pthread_detach(my_thread) != 0) {
		write(2, "pthread_detach", 14);
		return 1;
	}
	printf("Thread detached successfully\n");
	return 0;
}
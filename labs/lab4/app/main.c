#include "lib.h"
#include "types.h"

#define N 5

void philosopher(int i, sem_t forks[N]) {
	while (1) {
		printf("Philosopher %d: think.\n", i);
		sleep(128);
		if (i % 2 == 0) {
			sem_wait(&forks[i]);
			sleep(128);
			sem_wait(&forks[(i + 1) % N]);
			sleep(128);
		} else {
			sem_wait(&forks[(i + 1) % N]);
			sleep(128);
			sem_wait(&forks[i]);
			sleep(128);
		}
		printf("Philosopher %d: eat.\n", i);
		sleep(128);
		sem_post(&forks[i]);
		sleep(128);
		sem_post(&forks[(i + 1) % N]);
		sleep(128);
	}
}

void producer(int i, sem_t empty, sem_t full, sem_t mutex) {
	while (1) {
		sem_wait(&empty);
		sleep(128);
		sem_wait(&mutex);
		sleep(128);
		printf("Producer %d: produce.\n", i);
		sleep(128);
		sem_post(&mutex);
		sleep(128);
		sem_post(&full);
		sleep(128);
	}
}

void consumer(int i, sem_t empty, sem_t full, sem_t mutex) {
	while (1) {
		sem_wait(&full);
		sleep(128);
		sem_wait(&mutex);
		sleep(128);
		printf("Consumer %d: consume.\n", i);
		sleep(128);
		sem_post(&mutex);
		sleep(128);
		sem_post(&empty);
		sleep(128);
	}
}

void writer(int i, sem_t write_mutex) {
	while (1) {
		sem_wait(&write_mutex);
		sleep(128);
		printf("Writer %d: write.\n", i);
		sleep(128);
		sem_post(&write_mutex);
		sleep(128);
	}
}

void reader(int i, sem_t write_mutex, sem_t count_mutex) {
	while (1) {
		sem_wait(&count_mutex);
		sleep(128);
		if (get_counter() == 0) {
			sem_wait(&write_mutex);
			sleep(128);
		}
		set_counter(get_counter() + 1);
		sem_post(&count_mutex);
		sleep(128);
		printf("Reader %d: read, total %d readers.\n", i, get_counter());
		sleep(128);
		sem_wait(&count_mutex);
		sleep(128);
		set_counter(get_counter() - 1);
		if (get_counter() == 0) {
			sem_post(&write_mutex);
			sleep(128);
		}
		sem_post(&count_mutex);
		sleep(128);
	}
}

int uEntry(void) {
	// For lab4.1
	// Test 'scanf' 
	int dec = 0;
	int hex = 0;
	char str[6];
	char cha = 0;
	int ret = 0;
	while(1) {
		printf("Input:\" Test %%c Test %%6s %%d %%x\"\n");
		ret = scanf(" Test %c Test %6s %d %x", &cha, str, &dec, &hex);
		printf("Ret: %d; %c, %s, %d, %x.\n", ret, cha, str, dec, hex);
		if (ret == 4) {
			break;
		}
	}
	exit();

	// For lab4.2
	// Test 'Semaphore'
	// int i = 4;
	//
	// sem_t sem;
	// printf("Father Process: Semaphore Initializing.\n");
	// ret = sem_init(&sem, 2);
	// if (ret == -1) {
	// 	printf("Father Process: Semaphore Initializing Failed.\n");
	// 	exit();
	// }
	//
	// ret = fork();
	// if (ret == 0) {
	// 	while( i != 0) {
	// 		i --;
	// 		printf("Child Process: Semaphore Waiting.\n");
	// 		sem_wait(&sem);
	// 		printf("Child Process: In Critical Area.\n");
	// 	}
	// 	printf("Child Process: Semaphore Destroying.\n");
	// 	sem_destroy(&sem);
	// 	exit();
	// }
	// else if (ret != -1) {
	// 	while( i != 0) {
	// 		i --;
	// 		printf("Father Process: Sleeping.\n");
	// 		sleep(128);
	// 		printf("Father Process: Semaphore Posting.\n");
	// 		sem_post(&sem);
	// 	}
	// 	printf("Father Process: Semaphore Destroying.\n");
	// 	sem_destroy(&sem);
	// 	exit();
	// }

	// For lab4.3
	// TODO: You need to design and test the philosopher problem.
	// Note that you can create your own functions.
	// Requirements are demonstrated in the guide.
	// sem_t forks[N];
	// for (int j = 0; j < N; j++) {
	// 	ret = sem_init(&forks[j], 1);
	// 	if (ret == -1) {
	// 		printf("Forks Initializing Failed.\n");
	// 		exit();
	// 	}
	// }
	// for (int j = 0; j < N; j++) {
	// 	ret = fork();
	// 	if (ret == 0) {
	// 		philosopher(j, forks);
	// 		exit();
	// 	}
	// }
	// while (1);
	// for (int j = 0; j < N; j++) {
	// 	sem_destroy(&forks[j]);
	// }

	// For lab4.4
	// Test consumer-producer problem
	// sem_t mutex;
	// sem_t empty;
	// sem_t full;
	// ret = sem_init(&mutex, 1);
	// if (ret == -1) {
	// 	printf("Mutex Initializing Failed.\n");
	// 	exit();
	// }
	// ret = sem_init(&empty, N);
	// if (ret == -1) {
	// 	printf("Empty Mutex Initializing Failed.\n");
	// 	exit();
	// }
	// ret = sem_init(&full, 0);
	// if (ret == -1) {
	// 	printf("Full Mutex Initializing Failed.\n");
	// 	exit();
	// }
	// constexpr int num_producers = 4;
	// constexpr int num_consumers = 1;
	// for (int j = 0; j < num_producers; j++) {
	// 	ret = fork();
	// 	if (ret == 0) {
	// 		producer(j, empty, full, mutex);
	// 		exit();
	// 	}
	// }
	// for (int j = 0; j < num_consumers; j++) {
	// 	ret = fork();
	// 	if (ret == 0) {
	// 		consumer(j, empty, full, mutex);
	// 		exit();
	// 	}
	// }
	// while (1);
	// sem_destroy(&mutex);
	// sem_destroy(&empty);
	// sem_destroy(&full);

	// For lab4.5
	// reader-writer problem
	// sem_t write_mutex;
	// sem_t count_mutex;
	// ret = sem_init(&write_mutex, 1);
	// if (ret == -1) {
	// 	printf("Writer Mutex Initializing Failed.\n");
	// 	exit();
	// }
	// ret = sem_init(&count_mutex, 1);
	// if (ret == -1) {
	// 	printf("Reader Count Mutex Initializing Failed.\n");
	// 	exit();
	// }
	// constexpr int num_writers = 3;
	// constexpr int num_readers = 3;
	// for (int j = 0; j < num_writers; j++) {
	// 	ret = fork();
	// 	if (ret == 0) {
	// 		writer(j, write_mutex);
	// 		exit();
	// 	}
	// }
	// for (int j = 0; j < num_readers; j++) {
	// 	ret = fork();
	// 	if (ret == 0) {
	// 		reader(j, write_mutex, count_mutex);
	// 		exit();
	// 	}
	// }
	// while (1);
	// sem_destroy(&write_mutex);
	// sem_destroy(&count_mutex);
	return 0;
}

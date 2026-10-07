#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int main() {
	clock_t main_start = clock();
	printf("I am %d (main), my parent is %d \n", getpid(), getppid());
	for (int i = 0; i < 2; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			clock_t start = clock();
			printf("I am %d (child), my parent is %d \n", getpid(), getppid());
			for (int k = 0; k < 1000000; k++) {}
			clock_t end = clock();
			double ms = ((double)(end - start) * 1000) / CLOCKS_PER_SEC;
			printf("I am %d (child), I finished in %.2f miliseconds \n", getpid(), ms);
			exit(0);
		}
	}
	for (int i = 0; i < 2; i++) wait(NULL);
	clock_t main_end = clock();
	double ms = ((double)(main_end - main_start) * 1000) / CLOCKS_PER_SEC;
	printf("I am %d (parent), I finished in %.2f miliseconds \n", getpid(), ms);
	exit(0);
	return 0;
	
} 

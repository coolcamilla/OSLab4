#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++) {
		pid_t pid;
		pid = fork();
		sleep(5);
		
		// Exactly 5 forks (run the program using ./ex2 5)
		//if (pid > 0) {
		//	sleep(5);
		//	return 0;
		//}
	}
	//sleep(5);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
	char input[1024];
	char* args[64];
	
	while (true) {
		printf("simplistic_shell> ");
		fflush(stdout);
		
		if (fgets(input, sizeof(input), stdin) == NULL) break;
		
		input[strcspn(input, "\n")] = '\0';
		
		if (strlen(input) == 0) continue;
		if (strcmp(input, "exit") == 0) break;
		
		int i = 0;
		char* token = strtok(input, " ");
		while (token != NULL) {
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;
		
		int bg = 0;
		if (i > 0 && strcmp(args[i-1], "bg") == 0) {
			bg = 1;
			args[i-1] = NULL;
		}
		
		pid_t pid;
		pid = fork();
		
		if (pid == 0) {
			if (execvp(args[0], args) == -1) perror("Exec failed");
			exit(1);
		} else {
			if (bg == 0) waitpid(pid, NULL, 0);
			else printf("Process %d running in background \n", pid);
		}
		
	}
	return 0;
}

// I divided user's input into tokens. Then I used function execvp which takes string 
// tokens and outsources the work to the shell.

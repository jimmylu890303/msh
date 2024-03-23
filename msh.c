#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKENS  20 

int get_cmd(char *input_cmds, char * (*argv)[])
{
	// if no input => return
	if(strlen(input_cmds)<=1){
		printf("Please input command\n");
		return 0;
	}
	char *token;
	char *tokens[MAX_TOKENS]; 
	int count = 0;

	// parse input command 
    token = strtok(input_cmds, " ");
	while (token != NULL && count < MAX_TOKENS) {
		tokens[count] = token;
		count++;
		token = strtok(NULL, " ");
	}

	int i;
    for (i=0; i < count; i++) {
		if(tokens[i]==NULL)
			break;
		(*argv)[i] = strtok(tokens[i], "\n");
    }
	(*argv)[i] = NULL;
	return count;
}

int main(void)
{
	char input[4096];
	char *argv[MAX_TOKENS];
	int cmd_count;
	do {
		printf("msh> ");
		fgets(input, sizeof(input), stdin);
		cmd_count = get_cmd(input,&argv);
		if (!cmd_count)
			continue;
		
		pid_t pid;
		pid = fork();
		if(pid ==0){
			execvp(argv[0], argv);
			exit(0);
		}
		else if(pid>0){
			wait(NULL);
		}
		else
			printf("fork error");

	} while(!cmd_count || strstr(argv[0], "exit") == NULL);

	return 0;
}

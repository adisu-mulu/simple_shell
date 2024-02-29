#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{

	while (1)
	{

	printf("$: ");	
	char path[] = "/bin/"; //path to be added to the beginning of every command
	char *token, *cmd[10], *delim = " ";

	//get the command from the user
	char *str = NULL;
	size_t n;
	char *delimiter ="\n";
	getline(&str, &n, stdin);

	//getline appends newline to the string by default, so remove it
	str[strcspn(str,"\n")]='\0';
	

	//create a pointer to string which will be used to store the complete command
	char *command_and_arguements =malloc(strlen(path) + strlen(str) + 1);
	
	//copy the path to the prepared buffer
	strcpy(command_and_arguements, path);
	
	//append / concatenate the command to the path
	strcat(command_and_arguements, str);
	
	//tokenize the whole string into array of string literls so that the first literl is taken as command and the rest as arguements
	token =strtok(command_and_arguements, delim);
	int x=0;
	//store each token as a string literai
	while (token != NULL)
	{
			cmd[x]=token;  
			token = strtok(NULL, delim);
			x++;
			}
	cmd[x]=NULL; //append NULL to the end of the array of pointers to strings because execve takes as 2nd arguement array of pointers to strings terminated by NULL	
	
	pid_t pid;
	pid=fork();

	if(pid==0)
	{
	//execute the command
	execve(cmd[0],cmd, NULL);
	free(command_and_arguements);
	}

	else{
		wait(NULL);
		free(command_and_arguements);
	//free dynamic memories
	}

	}
	
	//execve(cmd[0],cmd,NULL);
	return (0);
}

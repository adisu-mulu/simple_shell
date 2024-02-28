#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include "main.h"
/**
 * main - function
 * @argc: arguement number
 * @argv: command line arguement
 * Return: 0 if success
 */

int main(int argc, char *argv[])
{
	while (1)
	{
		char pathWithCommand[250];
		char *cmds[10];
		int y = 0;
		size_t n;
		pid_t pid;
		pid_t child_pid;
		int x;
		char *tkwpCopy = NULL;
		char *token_command_with_path = NULL;
		char *input_symbol = "$ ";
		char *user_command = NULL;
		char *token = NULL;

		if (argc == 1)
			write(1, input_symbol, custom_strlen(input_symbol));

		if (getline(&user_command, &n, stdin) == -1)
		{
			free(user_command);
			exit(1);
		}
		if(custom_strcmp(user_command,  "\n") == 0)
			continue;

		user_command[custom_strcspn(user_command, "\n")] = '\0';
		tkwpCopy = custom_strdup(user_command);
		token_command_with_path = strtok(tkwpCopy, " ");
		x = 0;
		

		while (token_command_with_path != NULL)
		{
			cmds[x] = token_command_with_path;
			token_command_with_path = strtok(NULL, " ");
			x++;
		}
		cmds[x] = NULL;
		if (custom_strcmp(cmds[0], "exit") == 0 || custom_strcmp(cmds[0], "/bin/exit") == 0)
		{
			exit(0);
		}
		else if (custom_strcmp(cmds[0], "env") == 0)
		{
			extern char **environ;
			char **env = environ;

			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
			y = 3;
		}
		else if (access(cmds[0], X_OK) == 0)
		{
			y = 1;
		}
		else
		{
			char *path = custom_getenv("PATH");
			char *path_copy = strdup(path);
			

			strtok(NULL, " ");
			token = strtok(path_copy, ":");

			while (token != NULL)
			{
				custom_strcpy(pathWithCommand, token);
				custom_strcpy(pathWithCommand + custom_strlen(token), "/");
				custom_strcpy(pathWithCommand + custom_strlen(token) + 1, cmds[0]);
				if (access(pathWithCommand, X_OK) == 0)
				{
					y = 2;
					break;
				}
				token = strtok(NULL, ":");
			}
			free(path_copy);
		}
		if (y == 1)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(cmds[0], cmds, NULL);
			}
			else
				wait(NULL);
		}
		else if (y == 2)
		{
			if (argc > 1)
			{
				int pipe_fd[2];

				if (pipe(pipe_fd) == -1)
				{
					perror("pipe");
					exit(1);
				}
				child_pid = fork();

				if (child_pid == -1)
				{
					perror("fork");
					exit(1);
				}
				if (child_pid == 0)
				{
					close(pipe_fd[1]);
					dup2(pipe_fd[0], STDIN_FILENO);
					execve(pathWithCommand, cmds, NULL);
					exit(0);
				}
				else
				{
					close(pipe_fd[0]);
					dup2(pipe_fd[1], STDOUT_FILENO);
					execve(cmds[0], cmds, NULL);
				
					exit(0);
				}
				
			}
			else
			{
				pid = fork();
				if (pid == 0)
				{
					execve(pathWithCommand, cmds, NULL);
				}
				else
				{
					wait(NULL);
				}
			}
		}
		else if (y == 0)
		{
			printf("%s: 1: %s: not found\n", argv[0], user_command);
		}
		free(user_command);
		free(tkwpCopy);
		
	}
	printf("\n");
	return (0);
}

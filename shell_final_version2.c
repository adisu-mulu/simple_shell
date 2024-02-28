#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include "main.h"


#define MAX_CMDS 10
#define MAX_PATH 250


/**
 * main - function
 * @argc: integer
 * @argv: char
 * Return: 0
 */
int main(int argc, char *argv[])
{
	if (argv)
	while (1)
	{
		char *cmds[MAX_CMDS];
		size_t n;
		char *user_command = NULL, *token_command_with_path = NULL;
		char *input_symbol = "$ ";
		int x;
		char *tkwpCopy = NULL;

		if (argc == 1 && isatty(STDIN_FILENO))
			write(1, input_symbol, custom_strlen(input_symbol));
		if (getline(&user_command, &n, stdin) == -1)
		{
			free(tkwpCopy);
			free(user_command);
			exit(1);
		}

		if (custom_strcmp(user_command, "\n") == 0)
		{
			continue;
		}

		user_command[custom_strcspn(user_command, "\n")] = '\0';
		tkwpCopy = custom_strdup(user_command);
		token_command_with_path = strtok(tkwpCopy, " ");
		x = 0;

		while (token_command_with_path != NULL && x < MAX_CMDS - 1)
		{
			cmds[x++] = token_command_with_path;
			token_command_with_path = strtok(NULL, " ");
		}
		cmds[x] = NULL;

		if (custom_strcmp(cmds[0], "exit") == 0)
		{
			free(tkwpCopy);
			handle_exit(user_command);
		}

		if (custom_strcmp(cmds[0], "/bin/exit") == 0)
		{
			free(tkwpCopy);
			handle_exit(user_command);
		}

		else if (custom_strcmp(cmds[0], "env") == 0)
			handle_env(__environ);
		else
		{
			char pathWithCommand[MAX_PATH];

			execute_command(cmds, argc, pathWithCommand);
		}
		free(tkwpCopy);
		free(user_command);	
	}
	return (0);
}

/**
 * execute_command - function
 * @cmds: char
 * @argc: integer
 * @pathWithCommand: char
 * Return: nothing
 */
void execute_command(char *cmds[], int argc, char *pathWithCommand)
{
	int y = 0;
	pid_t pid, child_pid;

	if (access(cmds[0], X_OK) == 0)
		y = 1;
	else
	{
		char *path = custom_getenv("PATH");
		char *path_copy = custom_strdup(path);
		char *token = strtok(path_copy, ":");

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
			execve(cmds[0], cmds, NULL);
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
				execve(pathWithCommand, cmds, NULL);
				exit(0);
			}
		}
		else
		{
			pid = fork();

			if (pid == 0)
				execve(pathWithCommand, cmds, NULL);
			else
				wait(NULL);
		}
	}
	else if (y == 0)
		printf("%s: 1: %s: not found\n", cmds[0], cmds[0]);
}

/**
 * handle_exit - function
 * @user_command: char
 * Return: nothing
 */
void handle_exit(char *user_command)
{
	free(user_command);
	exit(0);
}

/**
 * handle_env - function
 * @env: character
 * Return: nothing
 */
void handle_env(char **env)
{
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}


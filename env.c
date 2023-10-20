#include "main.h"

/**
 * print_env - Prints the environment variables
 *
 * Return: Nothing
 */
void print_env(void)
{
	char **env = environ;

	while (*env)
	{
		_printf("%s\n", *env);
		env++;
	}
}

/**
 * command_exists - Checks if a command exists
 * @cmd: The command to check
 *
 * Return: The command if it exists, otherwise NULL
 */
char *command_exists(char *cmd)
{
	char *cmd_path;
	char *path;
	char temp_cmd[MAX_CMD_LEN];

	if (access(cmd, X_OK) == 0)
		return (cmd);

	cmd_path = my_strdup(my_getenv("PATH"));
	if (cmd_path == NULL)
		return (NULL);

	path = my_strtok(cmd_path, ":");
	while (path != NULL)
	{
		int path_len = my_strlen(path);
		int cmd_len = my_strlen(cmd);

		if (path_len + cmd_len + 2 <= MAX_CMD_LEN)
		{
			my_strcpy(temp_cmd, path);
			temp_cmd[path_len] = '/';
			my_strcpy(temp_cmd + path_len + 1, cmd);

			if (access(temp_cmd, X_OK) == 0)
			{
				cmd = my_strdup(temp_cmd);
				free(cmd_path);
				return (cmd);
			}
		}

		path = my_strtok(NULL, ":");
	}
	free(cmd_path);

	return (NULL);
}


/**
 * execute_command - Executes a command
 * @cmd: The command to execute
 * @argv: The arguments for the command
 *
 * Return: Nothing
 */
void execute_command(char *cmd, char **argv)
{
	pid_t pid;
	int status;

	/* If the command is "exit", exit with the provided status */
	if (my_strcmp(cmd, "exit") == 0)
	{
		status = argv[1] ? my_atoi(argv[1]) : 0;
		exit(status);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("Fork error");
		exit(1);
	}
	else if (pid == 0)
	{  /* Child process */
		if (execve(cmd, argv, environ) == -1)
		{
			perror("Execve error");
			exit(1);
		}
	}

	/* Parent process */
	pid = waitpid(pid, &status, 0);
	if (pid < 0)
		perror("Waitpid error");
}

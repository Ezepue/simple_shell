#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * read_line - Read a line of text from the standard input.
 *
 * Return: A dynamically allocated string containing the input line.
 */
char *read_line(void)
{
	char *line = malloc(1024);
	size_t len = 1024;

	if (isatty(STDIN_FILENO))
		_printf("$ ");
	fflush(stdout);
	if (my_getline(&line, &len, stdin) == -1)
	{
		return (NULL);
	}
	return (line);
}

/**
 * tokenize_line - Tokenizes a line of input
 * @line: The line to tokenize
 * @cmds: The commands structure
 *
 * Return: Nothing
 */
void tokenize_line(char *line, cmd_t *cmds)
{
	int i = 0;
	char *token = strtok(line, " \n");

	while (token != NULL)
	{
		cmds->argv[i] = my_strdup(token);
		i++;
		token = strtok(NULL, " \n");
	}
	cmds->arg_count = i;
	cmds->argv[i] = NULL;
	free(line);
}

/**
 * process_commands - Processes the commands
 * @cmds: The commands structure
 *
 * Return: Nothing
 */
void process_commands(cmd_t *cmds)
{
	char *tmp;

	if (specials(cmds))
		return;
	if (count_slash(cmds->argv[0]) > 0)
	{
		tmp = cmds->argv[0];
		cmds->argv[0] = get_cmd(cmds->argv[0]);
		free(tmp);
	}
	tmp = cmds->argv[0];
	cmds->argv[0] = command_exists(cmds->argv[0]);
	if (cmds->argv[0] == NULL)
	{
		_printf("%s: command not found\n", tmp);
		free(tmp);
		return;
	}
	free(tmp);
	execute_command(cmds->argv[0], cmds->argv);
}

/**
 * main - Entry point of the program.
 * @argc: Argument count
 * @args: Argument vector
 *
 * This function allocates memory for a cmd_t structure, initializes it,
 * and copies the environment. It then enters an infinite loop where it reads
 * a line from the user, tokenizes the line, and processes the commands.
 * After the loop, it frees the allocated memory and returns EXIT_SUCCESS.
 *
 * Return: Always EXIT_SUCCESS.
 */
int main(int argc, char *args[])
{
	char *line = NULL;
	cmd_t *cmds = (cmd_t *)malloc(sizeof(cmd_t));
	bool piped = false;

	init_cmdt(cmds);
	copy_environ(cmds);
	while (!piped)
	{
		cmds->argv = (char **)malloc(1024 * sizeof(char *));
		if (argc == 2)
		{
			line = readlines(args[1]);
			piped = true;
		}
		else
			line = read_line();
		if (line == NULL)
		{
			free(cmds->argv);
			free_cmdt(cmds);
			exit(EXIT_SUCCESS);
		}
		line = rmv_space(line);
		tokenize_line(line, cmds);
		if (cmds->argv[0] == NULL)
		{
			free_args((cmds));
			continue;
		}
		process_commands(cmds);
		free_args(cmds);
	}
	free_cmdt(cmds);
	return (EXIT_SUCCESS);
}

#include "main.h"
#include <stdio.h>

/**
 * read_line - Read a line of text from the standard input.
 *
 * Return: A dynamically allocated string containing the input line.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t gline = 0;

	if (isatty(STDIN_FILENO))
		_printf("$ ");
	fflush(stdout);
	gline = getline(&line, &len, stdin);
	if (gline == -1)
	{
		free(line);
		exit(0);
	}
	else if (gline == 1 && line[0] == 4)
		return (NULL);
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
	char *token = strtok(line, " ");

	while (token != NULL)
	{
		cmds->argv[i] = my_strdup(token);
		i++;
		token = strtok(NULL, " ");
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
 *
 * This function allocates memory for a cmd_t structure, initializes it,
 * and copies the environment. It then enters an infinite loop where it reads
 * a line from the user, tokenizes the line, and processes the commands.
 * After the loop, it frees the allocated memory and returns EXIT_SUCCESS.
 *
 * Return: Always EXIT_SUCCESS.
 */
int main(void)
{
	char *line = NULL;
	cmd_t *cmds = (cmd_t *)malloc(sizeof(cmd_t));

	init_cmdt(cmds);
	copy_environ(cmds);

	cmds->argv = (char **)malloc(1024 * sizeof(char *));
	while (1)
	{
		line = read_line();
		if (line == NULL)
			continue;
		line = rmv_space(line);
		line = strtok(line, "\n");
		tokenize_line(line, cmds);
		if (cmds->argv[0] == NULL)
		{
			free_args((cmds));
			continue;
		}
		process_commands(cmds);
		free_args(cmds);
	}
	
    free(cmds->argv);
	free_cmdt(cmds);
	return (EXIT_SUCCESS);
}

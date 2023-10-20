#include "main.h"

/**
 * free_args - Frees memory allocated for command arguments.
 * @cmds: A pointer to the command structure.
 */
void free_args(cmd_t *cmds)
{
	int i = 0;

	while (i < cmds->arg_count)
	{
		free(cmds->argv[i]);
		i++;
	}
	free(cmds->argv);
}

/**
 * my_getenv - Get the value of an environment variable by name.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable if found,
 * or NULL if not found.
 */
char *my_getenv(const char *name)
{
	int i;

	if (name == NULL || environ == NULL)
		return (NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		const char *env_var = environ[i];
		size_t name_len = my_strlen(name);

		if (my_strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
			return ((char *)&env_var[name_len + 1]);
	}

	return (NULL);
}

/**
 * rmv_space - Remove extra spaces and tabs from a string.
 * @cmd: The input string with potential extra spaces and tabs.
 *
 * Return: A new string with extra spaces and tabs removed.
 */
char *rmv_space(char *cmd)
{
	int i, j = 0;
	char *cmd_clean;
	bool prev_space = (cmd[0] == ' ' || cmd[0] == '\t');

	cmd_clean = malloc(my_strlen(cmd) + 1);

	for (i = 0; cmd[i] != '\0'; i++)
	{
		if (cmd[i] == ' ' || cmd[i] == '\t')
		{
			if (!prev_space)
				cmd_clean[j++] = cmd[i];
			prev_space = true;
		}
		else
		{
			cmd_clean[j++] = cmd[i];
			prev_space = false;
		}
	}
	cmd_clean[j] = '\0';
	free(cmd);
	cmd = cmd_clean;
	return (cmd);
}

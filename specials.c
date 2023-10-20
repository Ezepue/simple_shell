#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
 * specials - Checks for special commands and executes them
 * @cmds: The commands to check
 *
 * Return: true if a special command was executed, otherwise false
 */
bool specials(cmd_t *cmds)
{
	/* Check for the exit command */
	if (my_strcmp(cmds->argv[0], "exit") == 0)
	{
		free_args(cmds);
		free_cmdt(cmds);
		exit(0);
	}

	/* Check for the env command */
	if (my_strcmp(cmds->argv[0], "env") == 0)
	{
		print_env();
		return (true);
	}

	if (my_strcmp(cmds->argv[0], "setenv") == 0)
	{
		cmds->setenv = true;
		my_setenv(cmds);
		return (true);
	}

	if (my_strcmp(cmds->argv[0], "unsetenv") == 0)
	{
		my_unsetenv(cmds);
		return (true);
	}

	return (false);
}

/**
 * copy_environ - Copies the environment variables
 * @cmds: The commands structure
 *
 * Return: Nothing
 */
void copy_environ(cmd_t *cmds)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
		;

	cmds->env = (char **)malloc((i + 1) * sizeof(char *));

	for (i = 0; environ[i] != NULL; i++)
	{
		cmds->env[i] = environ[i];
	}

	cmds->env[i] = NULL;
	environ = cmds->env;
	free(cmds->env);
}

/**
 * my_setenv - Sets an environment variable
 * @cmds: The commands structure
 *
 * Return: 1 on success, otherwise 0
 */
int my_setenv(cmd_t *cmds)
{
	char new_value[1024], *n_value = NULL, *temp = NULL;
	char *param = NULL, *value = NULL;
	char **new_env;
	int i, count;

	param = cmds->argv[1];
	value = cmds->argv[2];
	count = cmds->new_env_count;
	my_strcpy(new_value, param);
	my_strcat(new_value, "=");
	my_strcat(new_value, value);
	cmds->new_env[count] = my_strdup(new_value);
	n_value = cmds->new_env[count];
	for (i = 0; environ[i] != NULL; i++)
	{
		if (my_strncmp(n_value, environ[i], my_strlen(param)) == 0)
		{
			temp = environ[i];
			environ[i] = (n_value);
			free(temp);
			(cmds->new_env_count)++;
			return (1);
		}
	}
	for (i = 0; environ[i] != NULL; i++)
		;
	new_env = malloc((i + 2) * sizeof(char *));
	for (i = 0; environ[i] != NULL; i++)
	{
		new_env[i] = environ[i];
	}
	new_env[i] = (n_value);
	new_env[i + 1] = NULL;

	free(cmds->env);
	cmds->env = new_env;
	environ = cmds->env;
	(cmds->new_env_count)++;
	return (1);
}

/**
 * my_unsetenv - Remove an environment variable.
 * @cmds: The command structure containing arguments.
 *
 * Return: 0 on success, otherwise 1
 */
int my_unsetenv(cmd_t *cmds)
{
	int i = 0, j = 0;
	char **new_env, *name = cmds->argv[1];

	while (environ[i] != NULL)
		i++;

	new_env = (char **)malloc((i + 1) * sizeof(char *));
	if (new_env == NULL)
		return (1);

	i = 0;
	while (environ[i] != NULL)
	{
		if (my_strncmp(name, environ[i], my_strlen(name)) != 0)
		{
			new_env[j] = environ[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;

	free(cmds->env);
	cmds->env = new_env;
	environ = cmds->env;

	return (0);
}

/**
 * free_cmdt - Frees the memory allocated for the cmd_t structure.
 *
 * @cmds: The cmd_t structure to be freed.
 *
 * This function frees the memory allocated for the cmd_t structure
 * and its associated elements. If the setenv field of cmds is not NULL,
 * it also frees the memory allocated for the new_env field. It then
 * frees the memory allocated for the env field and finally frees cmds itself.
 */
void free_cmdt(cmd_t *cmds)
{
	int i;


	for (i = 0; i < cmds->new_env_count; i++)
	{
		free(cmds->new_env[i]);
		cmds->new_env[i] = NULL;
	}
	free(cmds->env);
	free(cmds);
}

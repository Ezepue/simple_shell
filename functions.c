#include "main.h"

/**
 * my_strncmp - Compares two strings up to n characters.
 *
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 * @n: The maximum number of characters to be compared.
 *
 * Return: 0 if the strings are equal, -1 if s1 is less than s2,
 *         or 1 if s1 is greater than s2.
 */
int my_strncmp(const char *s1, const char *s2, int n)
{
	int i = 0;

	while (i < n && *s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
		i++;
	}

	if (i == n)
		return (0);
	else if (*s1 < *s2)
		return (-1);
	else if (*s1 > *s2)
		return (1);

	return (0);
}

/**
 * my_strcat - Concatenates two strings
 * @dest: The destination string
 * @src: The source string
 *
 * Return: A pointer to the destination string
 */
char *my_strcat(char *dest, const char *src)
{
	while (*dest)
		dest++;

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (dest);
}

/**
 * init_cmdt - Initializes the cmd_t structure.
 *
 * @cmds: The cmd_t structure to be initialized.
 *
 * This function initializes the fields of the cmd_t structure.
 * It sets the env field to NULL, path_found to false, and setenv to false.
 */
void init_cmdt(cmd_t *cmds)
{
	/*cmds->new_env = (char **)malloc(sizeof(char *) * 5);*/
	cmds->env = NULL;
	cmds->path_found = false;
	cmds->arg_count = 0;
	cmds->setenv = false;
	cmds->new_env_count = 0;
}

/**
 *count_slash - Counts number of forward slashes in an input string
 *@str: Input string
 *
 *This function is useful to check if a command was passed using
 *its absolute path, for example "/bin/ls" instead of "ls."
 *
 *Return: Number of forward slashes
 */
int count_slash(char *str)
{
	int i, len, slash = 0;

	len = my_strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '/')
			slash++;
	}
	return (slash);
}

/**
 *get_cmd - Extracts command if absolute path was passed.
 *@str: Absolute path of command.
 *
 *
 *Return: Command, or NULL if failed.
 */
char *get_cmd(char *str)
{
	int i, j = 0, slash_point = 0, len;
	char *cmd;

	len = my_strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '/')
			slash_point = i;
	}
	cmd = malloc(len - slash_point + 1);
	if (!cmd)
	{
		perror("get_cmd");
		return (NULL);
	}
	for (i = slash_point + 1; i < len; i++)
		cmd[j++] = str[i];
	cmd[j] = '\0';
	return (cmd);
}

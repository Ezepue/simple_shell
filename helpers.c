#include "main.h"

/**
 * my_strcmp - Compares two strings.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: 0 if both are NULL or equal, -1
 * if s1 is NULL or less than s2,
 * 1 if s2 is NULL or greater than s1.
 */
int my_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 < *s2)
		return (-1);
	else if (*s1 > *s2)
		return (1);

	return (0);
}

/**
 * my_strcpy - Copies the string pointed to by src to dest.
 * @dest: The destination where the content is to be copied.
 * @src: The source string to be copied.
 */
void my_strcpy(char *dest, const char *src)
{
	if (dest == NULL || src == NULL)
	{
		return;
	}

	while ((*dest++ = *src++))
		;
}

/**
 * my_strlen - Returns the length of a string.
 * @s: The string to be measured.
 *
 * Return: The length of the string.
 */
int my_strlen(const char *s)
{
	int len = 0;

	if (s == NULL)
	{
		return (0);
	}
	while (*s++)
		len++;
	return (len);
}

/**
 * my_strdup - Duplicates a string.
 * @str: The source string to be duplicated.
 *
 * Return: A pointer to the duplicated string.
 * It returns NULL if insufficient memory was available.
 */
char *my_strdup(const char *str)
{
	char *result;

	if (str == NULL)
	{
		return (NULL);
	}
	result = malloc(my_strlen(str) + 1);

	if (result == NULL)
	{
		perror("Error: ");
		return (NULL);
	}

	my_strcpy(result, str);
	return (result);
}


/**
 * my_atoi - Converts a string to an integer
 * @str: The string to be converted.
 *
 * Return: The converted integer value from the string str.
 */
int my_atoi(const char *str)
{
	int result = 0, sign = 1;

	if (str == NULL)
	{
		return (0);
	}

	while (*str == ' ')
	{
		str++;
	}

	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			sign = -1;
		}
		str++;
	}

	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}

	return (sign * result);
}

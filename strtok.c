#include "main.h"

/**
 * my_strtok - Tokenize a string based on a delimiter.
 * @str: The string to tokenize.
 * @delim: The delimiter to use for tokenization.
 *
 * Return: A pointer to the next token or NULL if there are no more tokens.
 */
char *my_strtok(char *str, const char *delim)
{
	static char *token;
	static char *nextToken;

	if (str != NULL)
	{
		token = str;
		nextToken = str;
	}

	if (token == NULL)
		return (NULL);

	while (*nextToken != '\0' && my_strchr(delim, *nextToken) != NULL)
		nextToken++;

	if (*nextToken == '\0')
		return (NULL);

	token = nextToken;
	while (*nextToken != '\0' && my_strchr(delim, *nextToken) == NULL)
		nextToken++;

	if (*nextToken != '\0')
	{
		*nextToken = '\0';
		nextToken++;
	}

	return (token);
}

/**
 * my_strchr - Find the first occurrence of a character in a string.
 * @str: The string to search.
 * @character: The character to find.
 *
 * Return: A pointer to the first occurrence of the character in the string
 *         or NULL if the character is not found.
 */
char *my_strchr(const char *str, int character)
{
	while (*str != '\0')
	{
		if (*str == character)
		{
			return ((char *)str);
		}
		str++;
	}

	return (NULL);
}

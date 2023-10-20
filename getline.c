#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define INITIAL_BUFFER_SIZE 1280
#define BUFFER_SIZE 1280

/**
 * my_realloc - Reallocate memory for a character buffer.
 * @line: Pointer to the current character buffer.
 * @buffer_size: Pointer to the size of the buffer.
 *
 * This function reallocates memory for a character buffer when needed.
 *
 * Return: A pointer to the reallocated buffer on success, or NULL on failure.
 */
char *my_realloc(char *line, size_t *buffer_size)
{
	size_t new_size = (*buffer_size) * 2, i;
	char *new_line = (char *)malloc(new_size);

	if (new_line == NULL)
	{
		perror("Memory allocation failed");
		free(line);
		return (NULL);
	}

	for (i = 0; i < *buffer_size; i++)
		new_line[i] = line[i];

	free(line);
	*buffer_size = new_size;
	return (new_line);
}

/**
 * my_getline - Read a line from a file stream.
 * @lineptr: Pointer to the buffer storing the line.
 * @n: Pointer to the size of the buffer.
 * @stream: File stream to read from.
 *
 * This function reads a line from the specified file stream, dynamically
 * reallocating memory when needed.
 *
 * Return: The number of characters read on success, or -1 on failure.
 */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
	char *line = *lineptr, buffer[BUFFER_SIZE], *new_line = NULL;
	int ch;
	size_t position = 0, buffer_position = 0, buffer_size = *n, bytes_read = 0;


	if (line == NULL)
	{
		line = (char *)malloc(buffer_size);
		if (line == NULL)
		{
			perror("Memory allocation failed");
			return (-1);
		}
	}
	while (1)
	{
		if (buffer_position >= bytes_read)
		{
			bytes_read = read(fileno(stream), buffer, BUFFER_SIZE);
			if (bytes_read == (size_t)-1)
			{
				perror("Read error");
				free(line);
				return (-1);
			}
			if (bytes_read == 0)
			{
				if (position == 0)
				{
					free(line);
					return (-1);
				}
				else
					line[position] = '\0';
					break;
			}
			buffer_position = 0;
		}
		ch = buffer[buffer_position++];
		line[position] = (char)ch;
		position++;
		if (position >= buffer_size - 1)
		{
			new_line = my_realloc(line, &buffer_size);
			if (new_line == NULL)
				return (-1);
			line = new_line;
		}
		if (ch == '\n')
		{
			line[position] = '\0';
			break;
		}
	}
	*lineptr = line;
	*n = buffer_size;
	return (position);
}

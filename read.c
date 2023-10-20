#include "main.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

/**
 *readlines - Reads from file
 *@arg_1: File path
 *
 * Return: Command.
 *
 */
char *readlines(char *arg_1)
{
	int file;
	size_t bytesRead = 0, totalRead = 0;
	char buffer[1024];

	file = open(arg_1, O_RDONLY);
	if (file == -1)
	{
		perror("Can't open file");
		exit(errno);
	}
	buffer[0] = '\0';
	while (1)
	{
		bytesRead = read(file, buffer, sizeof(buffer));
		totalRead += bytesRead;
		if (bytesRead == 0)
			break;
		if (bytesRead == (size_t)-1)
		{
			perror("Cannot read file");
			close(file);
			exit(errno);
		}
	}
	buffer[totalRead] = '\0';
	close(file);

	return (my_strdup(buffer));
}

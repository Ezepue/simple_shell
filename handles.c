#include "main.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * handle_char - Handles character format specifier.
 * @args: List of arguments.
 * @count: Pointer to the count of characters printed.
 */
void handle_char(va_list args, int *count)
{
	char c = va_arg(args, int);

	_putchar(c);
	(*count)++;
}

/**
 * handle_string - Handles string format specifier.
 * @args: List of arguments.
 * @count: Pointer to the count of characters printed.
 */
void handle_string(va_list args, int *count)
{
	char *sp;

	char *s = va_arg(args, char *);

	for (sp = s; *sp != '\0'; sp++)
	{
		_putchar(*sp);
		(*count)++;
	}
}

/**
 * handle_percent - Handles percent format specifier.
 * @count: Pointer to the count of characters printed.
 */
void handle_percent(int *count)
{
	_putchar('%');
	(*count)++;
}

/**
 * handle_int - Handles integer format specifier.
 * @args: List of arguments.
 * @count: Pointer to the count of characters printed.
 */
void handle_int(va_list args, int *count)
{
	int i = va_arg(args, int);

	if (i == 0)
	{
		_putchar('0');
		(*count)++;
	}
	else
	{
		print_int(i);
		(*count) += (i < 0) ? 2 : 1;
		while (i /= 10)
		{
			(*count)++;
		}
	}
}

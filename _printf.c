#include "main.h"

/**
 * print_negative - Prints the negative sign and negates the number.
 * @n: Pointer to the number to be negated.
 */
void print_negative(int *n)
{
	_putchar('-');
	*n = -*n;
}

/**
 * print_digit - Prints a digit.
 * @n: The number to be printed.
 */
void print_digit(int n)
{
	_putchar((n % 10 + '0'));
}

/**
 * print_int - Recursively prints an integer.
 * @n: The integer to be printed.
 */
void print_int(int n)
{
	if (n < 0)
	{
		print_negative(&n);
	}

	if (n / 10)
	{
		print_int(n / 10);
	}

	print_digit(n % 10);
}

/**
 * _printf - A Custom printf function.
 * @format: The format string.
 *
 * Return: The number of characters printed
 *(excluding the null byte used to end output to strings).
 */
int _printf(const char *format, ...)
{
	int count = 0;
	char *p;
	va_list args;

	va_start(args, format);

	for (p = (char *)format; *p != '\0'; p++)
	{
		if (*p != '%')
		{
			_putchar(*p);
			count++;
			continue;
		}

		p++;
		switch (*p)
		{
			case 'c':
				handle_char(args, &count);
				break;
			case 's':
				handle_string(args, &count);
				break;
			case '%':
				handle_percent(&count);
				break;
			case 'd':
			case 'i':
				handle_int(args, &count);
				break;
			default:
				return (-1);
		}
	}

	va_end(args);
	return (count);
}

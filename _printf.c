#include "main.h"

void print_buffer(char buffer[], int *buff_loc);

/**
 * _printf - Printf function
 * @format: format.
 * Return: generated chars.
 */
int _printf(const char *format, ...)
{
	int p, generated = 0, generated_chars = 0;
	int isDataLoaded, breadth, resolution, magnitude, buff_loc = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (p = 0; format && format[p] != '\0'; p++)
	{
		if (format[p] != '%')
		{
			buffer[buff_loc++] = format[p];
			if (buff_loc == BUFF_SIZE)
				print_buffer(buffer, &buff_loc);
			/* write(1, &format[p], 1);*/
			generated_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_loc);
			isDataLoaded = get_flags(format, &p);
			breadth = get_width(format, &p, list);
			resolution = get_precision(format, &p, list);
			magnitude = get_size(format, &p);
			++p;
			generated = handle_print(format, &p, list, buffer,
				isDataLoaded, breadth, resolution, magnitude);
			if (generated == -1)
				return (-1);
			generated_chars += generated;
		}
	}

	print_buffer(buffer, &buff_loc);

	va_end(list);

	return (generated_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_loc: Location at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_loc)
{
	if (*buff_loc > 0)
		write(1, &buffer[0], *buff_loc);

	*buff_loc = 0;
}


#include <stdarg.h>
#include <unistd.h>
#include "main.h"

int print_number(int n)
{
    int count = 0;
    char c;

    if (n < 0)
    {
        write(1, "-", 1);
        count++;
        if (n == -2147483648)
        {
            count += _printf("2147483648");
            return (count);
        }
        n = -n;
    }
    if (n / 10)
        count += print_number(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1);
    count++;
    return (count);
}

int _printf(const char *format, ...)
{
    int count = 0, i = 0;
    va_list args;
    char ch;

    if (format == NULL)
        return (-1);

    va_start(args, format);

    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == '\0')
                break;
            switch (format[i])
            {
                case 'c':
                    ch = (char) va_arg(args, int);
                    write(1, &ch, 1);
                    count++;
                    break;
                case 's':
                {
                    char *str = va_arg(args, char *);
                    int j = 0;
                    if (str == NULL)
                        str = "(null)";
                    while (str[j])
                    {
                        write(1, &str[j], 1);
                        count++;
                        j++;
                    }
                    break;
                }
                case '%':
                    write(1, "%", 1);
                    count++;
                    break;
                case 'd':
                case 'i':
                {
                    int num = va_arg(args, int);
                    count += print_number(num);
                    break;
                }
                default:
                    write(1, "%", 1);
                    write(1, &format[i], 1);
                    count += 2;
            }
        }
        else
        {
            write(1, &format[i], 1);
            count++;
        }
        i++;
    }

    va_end(args);
    return (count);
}

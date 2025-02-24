#include <unistd.h>
#include <stdarg.h>

void	ft_putstr(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(1, str, 1);
		*len += 1;
		str++;
	}
}

void	ft_putdigit(long long int nbr, int base, int *len)
{
	char	*hex = "0123456789abcdef";

	if (nbr < 0)
	{
		nbr = -nbr;
		*len += 1;
		write(1, "-", 1);
	}
	if (nbr >= base)
		ft_putdigit((nbr / base), base, len);
	*len += 1;
	write(1, &hex[nbr % base], 1);
}

int ft_printf(const char *format, ... )
{
	int	len;

	len = 0;
	va_list ptr;
	va_start(ptr, format);
	while (*format)
	{
		if(*format == '%' && (*(format + 1) == 's' || *(format + 1) == 'd' || *(format + 1) == 'x'))
		{
			format++;
			if (*format == 's')
				ft_putstr(va_arg(ptr, char *), &len);
			else if (*format == 'd')
				ft_putdigit((long long int)va_arg(ptr, int), 10, &len);
			else if (*format == 'x')
				ft_putdigit((long long int)va_arg(ptr, unsigned int), 16, &len);
		}
		else
		{
			len += 1;
			write(1, format, 1);
		}
		format++;
	}
	return (va_end(ptr),len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:59:02 by hiipek            #+#    #+#             */
/*   Updated: 2024/12/02 15:18:22 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (*str)
	{
		i += ft_putchar(*str);
		str++;
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		j;
	va_list	arg;

	va_start(arg, format);
	i = 0;
	j = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			j += determine_format(format[i], arg);
		}
		else
			j += ft_putchar(format[i]);
		i++;
	}
	va_end(arg);
	return (j);
}

int	determine_format(char format, va_list arg)
{
	if (format == 'c')
		return (ft_putchar((char)va_arg(arg, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(arg, char *)));
	else if (format == 'p')
		return (ft_putptr(va_arg(arg, unsigned long), "0123456789abcdef"));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(arg, int)));
	else if (format == 'u')
		return (ft_putnbr_unsigned(va_arg(arg, unsigned int)));
	else if (format == 'x')
		return (ft_putnbr_base(va_arg(arg, unsigned int), "0123456789abcdef"));
	else if (format == 'X')
		return (ft_putnbr_base(va_arg(arg, unsigned int), "0123456789ABCDEF"));
	else if (format == '%')
		return (ft_putchar('%'));
	ft_putchar('%');
	ft_putchar(format);
	return (2);
}

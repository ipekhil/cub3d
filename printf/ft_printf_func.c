/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:11:57 by hiipek            #+#    #+#             */
/*   Updated: 2024/12/02 19:12:36 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	pf_strlen(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}

int	ft_putnbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		i += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		i += ft_putnbr(n / 10);
	i += ft_putchar(n % 10 + '0');
	return (i);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int	i;

	i = 0;
	if (n >= 10)
		i += ft_putnbr_unsigned(n / 10);
	i += ft_putchar(n % 10 + '0');
	return (i);
}

int	ft_putnbr_base(unsigned long nbr, char *base)
{
	int				i;
	unsigned int	base_len;

	base_len = pf_strlen(base);
	i = 0;
	if (nbr >= base_len)
		i += ft_putnbr_base(nbr / base_len, base);
	i += ft_putchar(base[nbr % base_len]);
	return (i);
}

int	ft_putptr(unsigned long nbr, char *base)
{
	int	i;

	i = 0;
	if (nbr == 0)
	{
		i += ft_putstr("(nil)");
		return (i);
	}
	i += ft_putstr("0x");
	i += ft_putnbr_base(nbr, base);
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongmingu <gongmingu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:21:41 by mkong             #+#    #+#             */
/*   Updated: 2023/11/14 16:34:18 by gongmingu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_and_print(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar_va(va_arg(ap, int)));
	if (c == 's')
		return (ft_putstr_va(va_arg(ap, char *)));
	if (c == 'p')
		return (ft_putadd_va(va_arg(ap, unsigned long long)));
	if (c == 'd' || c == 'i' || c == 'u')
		return (ft_putnbr_va(va_arg(ap, int), c));
	if (c == 'x' || c == 'X')
		return (ft_puthex_va(va_arg(ap, int), c));
	if (c == '%')
		write(1, "%", 1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			len++;
			format++;
			check_and_print(*format, ap);
		}
		else
			write(1, format, 1);
		format++;
		len++;
	}
	va_end(ap);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:21:41 by mkong             #+#    #+#             */
/*   Updated: 2023/11/10 19:56:47 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	check_and_print(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar_va(va_arg(ap, int)));
	if (c == 's')
		return (ft_putstr_va(va_arg(ap, char *)));
	if (c == 'p')
		return ;
	if (c == 'd' || c == 'i')
		return (ft_putnbr_va(va_arg(ap, int)));
	if (c == 'u')
		return ;
	if (c == 'x')
		return ;
	if (c == 'X')
		return ;
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

int main()
{
	int a = 10;
	printf("address : %p \n", &a);
	ft_printf("first : %c %s %d",'a', "abcd", -2147483648);
}
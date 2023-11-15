/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:21:41 by mkong             #+#    #+#             */
/*   Updated: 2023/11/15 16:28:31 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_and_print(char c, va_list ap, int *len)
{
	if (c == 'c')
		return (ft_putchar_va(va_arg(ap, int), len));
	if (c == 's')
		return (ft_putstr_va(va_arg(ap, char *), len));
	if (c == 'p')
		return (ft_putadd_va(va_arg(ap, unsigned long long), len));
	if (c == 'd' || c == 'i' || c == 'u')
		return (ft_putnbr_va(va_arg(ap, int), c, len));
	if (c == 'x' || c == 'X')
		return (ft_puthex_va(va_arg(ap, int), c, len));
	if (c == '%')
		return (ft_putchar_va('%', len));
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
			format++;
			check_and_print(*format, ap, &len);
		}
		else
			ft_putchar_va(*format, &len);
		if (len == -1)
			return (-1);
		format++;
	}
	va_end(ap);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:21:41 by mkong             #+#    #+#             */
/*   Updated: 2023/11/09 17:36:00 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int	check_type(char c)
{
	if (c == 'c' || c == 'd' || c == 'i' || c == 'u' || c == '%')
		return (4);
	if (c == 's' || c == 'x')
		return (8);
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
			check_type(*format);
		}
	}
	return (len);
}

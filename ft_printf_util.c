/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongmingu <gongmingu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:50:31 by mkong             #+#    #+#             */
/*   Updated: 2023/11/13 15:53:42 by gongmingu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s)
	{
		s++;
		length++;
	}
	return (length);
}

int	ft_intlen(int n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

void	str_upper(char *s)
{
	while (*s)
	{
		if ('a' <= *s && *s <= 'z')
			*s -= 32;
		s++;
	}
}

char	*ft_itohex(int n, char c)
{
	char	*result;
	int		index;
	int		len;

	len = ft_intlen(n, 16);
	result = (char *)malloc(sizeof(char) * len);
	index = len;
	while (--index >= 0)
	{
		result[index] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	result[len] = '\0';
	if (c == 'X')
		str_upper(result);
	return (result);
}
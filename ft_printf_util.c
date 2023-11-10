/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:50:31 by mkong             #+#    #+#             */
/*   Updated: 2023/11/10 19:56:31 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*itohex(int n)
{
	char	*result;
	int		index;
	int		len;

	len = ft_intlen(n);
	result = (char *)malloc(sizeof(char) * len);
	index = len;
	while (--index >= 0)
	{
		result[index] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	result[len] = '\n';
	return (result);
}
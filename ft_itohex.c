/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:50:31 by mkong             #+#    #+#             */
/*   Updated: 2023/11/15 15:44:11 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ulllen(unsigned long long n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

static void	str_upper(char *s)
{
	while (*s)
	{
		if ('a' <= *s && *s <= 'z')
			*s -= 32;
		s++;
	}
}

char	*ft_tohex(unsigned long long n, char c)
{
	char			*result;
	int				index;
	int				len;

	if (c != 'p')
		n = (unsigned int) n;
	len = ft_ulllen(n, 16);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == 0)
		return (0);
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

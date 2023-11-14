/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:50:31 by mkong             #+#    #+#             */
/*   Updated: 2023/11/14 16:55:01 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_intlen(unsigned long long n, int base)
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

char	*ft_itohex(int n, char c)
{
	char			*result;
	int				index;
	int				len;
	unsigned int	p;

	p = n;
	len = ft_intlen(p, 16);
	result = (char *)malloc(sizeof(char) * len);
	index = len;
	while (--index >= 0)
	{
		result[index] = "0123456789abcdef"[p % 16];
		p /= 16;
	}
	result[len] = '\0';
	if (c == 'X')
		str_upper(result);
	return (result);
}
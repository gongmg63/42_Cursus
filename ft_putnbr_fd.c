/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:12:07 by mkong             #+#    #+#             */
/*   Updated: 2023/10/16 16:03:57 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_int_len(int n)
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

void	c_arr_reverse(char *s, int len)
{
	char	tmp;
	int		idx;

	idx = 0;
	while (idx < len - 1)
	{
		tmp = *(s + idx);
		*(s + idx) = *(s + len - 1);
		*(s + len - 1) = tmp;
		len--;
		idx++;
	}
}

void	*ft_itoa_no_malloc(int n, char *result)
{
	int		len;
	int		idx;

	len = check_int_len(n);
	idx = 0;
	*(result + len) = '\0';
	if (n == 0)
		*result = '0';
	if (n < 0)
	{
		*(result + len - 1) = '-';
		*(result + idx++) = (n % 10) * (-1) + '0';
		n = n / 10 * (-1);
	}
	while (n > 0)
	{
		*(result + idx++) = n % 10 + '0';
		n /= 10;
	}
	c_arr_reverse(result, len);
	return (result);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	result[12];

	ft_itoa_no_malloc(n, result);
	write(fd, result, ft_strlen(result));
}

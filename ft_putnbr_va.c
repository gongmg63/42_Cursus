/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_va.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongmingu <gongmingu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:53:09 by mkong             #+#    #+#             */
/*   Updated: 2023/11/13 14:48:15 by gongmingu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_va(int n)
{
	char	n_array[10];
	int		count;

	count = 0;
	if (n == 0)
		write(1, "0", 1);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(1, "-2147483648", 11);
			return ;
		}
		write(1, "-", 1);
		n = (-1) * n;
	}
	while (n != 0)
	{
		n_array[count] = n % 10 + '0';
		n /= 10;
		++count;
	}
	while (--count != -1)
		write(1, n_array + count, 1);
}

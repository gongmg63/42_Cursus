/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_va.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:53:09 by mkong             #+#    #+#             */
/*   Updated: 2023/11/14 16:52:44 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void rec_write(unsigned int n)
{
	char	num;

	num = '0';
	if (n != 0)
	{
		rec_write(n / 10);
		num += (n % 10);
		write (1, &num, 1);
	}
}

void	ft_putnbr_va(int n, char c)
{
	unsigned int	num;

	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (n < 0 && (c == 'i' || c == 'd'))
	{
		write(1, "-", 1);
		num = n * (-1);
	}
	else
		num = n;
	rec_write(num);
}

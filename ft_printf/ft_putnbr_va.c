/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_va.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:53:09 by mkong             #+#    #+#             */
/*   Updated: 2023/11/15 17:02:45 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	rec_write(unsigned int n, int *len)
{
	char	num;

	num = '0';
	if (n != 0)
	{
		rec_write(n / 10, len);
		if (*len == -1)
			return ;
		num += n % 10;
		ft_putchar_va(num, len);
	}
}

void	ft_putnbr_va(int n, char c, int *len)
{
	unsigned int	num;

	if (n == 0)
	{
		ft_putchar_va('0', len);
		return ;
	}
	if (n < 0 && (c == 'i' || c == 'd'))
	{
		ft_putchar_va('-', len);
		if (*len == -1)
			return ;
		num = n * (-1);
	}
	else
		num = n;
	rec_write(num, len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunnbr_va.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongmingu <gongmingu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:08:28 by gongmingu         #+#    #+#             */
/*   Updated: 2023/11/13 14:33:24 by gongmingu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putunnbr_va(unsigned int n)
{
	char	n_array[10];
	int		count;

	count = 0;
	if (n == 0)
		write(1, "0", 1);
	while (n != 0)
	{
		n_array[count] = n % 10 + '0';
		n /= 10;
		++count;
	}
	while (--count != -1)
		write(1, n_array + count, 1);
}

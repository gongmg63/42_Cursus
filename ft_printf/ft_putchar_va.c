/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_va.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:48:03 by mkong             #+#    #+#             */
/*   Updated: 2023/11/15 16:13:26 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_va(char c, int *len)
{
	int	n;

	n = write(1, &c, 1);
	if (n == -1)
		*len = -1;
	else
		*len += n;
}

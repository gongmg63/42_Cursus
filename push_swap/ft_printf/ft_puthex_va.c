/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_va.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:34:29 by gongmingu         #+#    #+#             */
/*   Updated: 2023/11/15 16:34:16 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex_va(unsigned long long n, char c, int *len)
{
	char	*hex;

	hex = ft_tohex(n, c);
	if (hex == 0)
	{
		*len = -1;
		return ;
	}
	ft_putstr_va(hex, len);
	free(hex);
}

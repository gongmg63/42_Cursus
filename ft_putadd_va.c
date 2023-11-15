/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd_va.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:06:22 by mkong             #+#    #+#             */
/*   Updated: 2023/11/15 16:30:58 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putadd_va(unsigned long long add, int *len)
{
	ft_putstr_va("0x", len);
	if (*len == -1)
		return ;
	ft_puthex_va(add, 'p', len);
}

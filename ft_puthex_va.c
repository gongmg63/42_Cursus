/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_va.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongmingu <gongmingu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:34:29 by gongmingu         #+#    #+#             */
/*   Updated: 2023/11/13 15:10:44 by gongmingu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

void	ft_puthex_va(int n, char c)
{
	char	*hex;

	hex = ft_itohex(n, c);
	ft_putstr_va(hex);
}

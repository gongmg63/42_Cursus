/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd_va.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongmingu <gongmingu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:28:59 by gongmingu         #+#    #+#             */
/*   Updated: 2023/11/13 16:57:20 by gongmingu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    ft_putadd_va(unsigned long long add)
{
    unsigned long long  l_add;

    l_add = (unsigned long long)add;
    ft_puthex_va(l_add, 'p');
}

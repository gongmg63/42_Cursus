/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_va.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:52:04 by mkong             #+#    #+#             */
/*   Updated: 2023/11/15 16:16:22 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_va(char *s, int *len)
{
	int	n;

	if (s == 0)
	{
		ft_putstr_va("(null)", len);
		return ;
	}
	n = write(1, s, ft_strlen(s));
	if (n == -1)
		*len = -1;
	else
		*len += n;
}

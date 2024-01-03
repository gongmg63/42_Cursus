/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:17:23 by mkong             #+#    #+#             */
/*   Updated: 2024/01/03 16:23:47 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long		result;
	int				sign;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str != 0)
	{
		if (!ft_isdigit(*str))
		{
			write (1, "Error\n", 6);
			exit(1);
		}
		result = 10 * result + *str - '0';
		str++;
	}
	return ((int)result * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:42:20 by mkong             #+#    #+#             */
/*   Updated: 2024/03/21 16:40:39 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long long		result;
	int				sign;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	if (*str == 0 || sign == -1)
		exit(1);
	while (*str != 0)
	{
		result = 10 * result + *str - '0';
		if (result == 2147483648 && sign == -1)
		{
			str++;
			continue ;
		}
		if (!ft_isdigit(*str) || ((int)result != result))
			exit(1);
		str++;
	}
	return ((int)result * sign);
}

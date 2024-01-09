/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:17:23 by mkong             #+#    #+#             */
/*   Updated: 2024/01/09 14:41:23 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	err_exit(void)
{
	write(2, "Error\n", 6);
	exit(1);
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
	if (*str == 0)
		err_exit();
	while (*str != 0)
	{
		result = 10 * result + *str - '0';
		if (result == 2147483648 && sign == -1)
		{
			str++;
			continue ;
		}
		if (!ft_isdigit(*str) || ((int)result != result))
			err_exit();
		str++;
	}
	return ((int)result * sign);
}

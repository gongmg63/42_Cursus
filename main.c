/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:47:03 by gongmingu         #+#    #+#             */
/*   Updated: 2023/11/13 22:05:05 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int main()
{
	int a = 10;
	void	*z;
	printf("   first : %c %s %d %u %% %x %X %p \n",'a', "abcd", -2147483648,4000000000,160, 160, &a);
	ft_printf("ft_first : %c %s %d %u %% %x %X %p \n",'a', "abcd", -2147483648,4000000000,160, 160, &a);
}
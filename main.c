/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:47:03 by gongmingu         #+#    #+#             */
/*   Updated: 2023/11/15 16:10:26 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int main()
{
	int a = 10;
	void	*z;
	int b,c,d,e;

	b = printf("   first : %c %s %d %u %% %x %X %p \n",'a', 0, -1,4000000000,160, -16, &a);
	c = ft_printf("ft_first : %c %s %d %u %% %x %X %p \n",'a', 0, -1,4000000000,160, -16, &a);
	d = printf("%s", "");
	e = ft_printf("%s", "");
	printf("p : %d f : %d \np : %d f : %d \n", b,c,d,e);
}
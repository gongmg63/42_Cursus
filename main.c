/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:51:16 by mkong             #+#    #+#             */
/*   Updated: 2023/11/17 19:51:10 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int		fd = open("abc", O_RDONLY);
	char	*a;

	a = get_next_line(fd);
	printf("main : %s \n", a);
	a = get_next_line(fd);
	printf("main 2 : %s \n", a);
	a = get_next_line(fd);
	printf("main 3 : %s \n", a);
}


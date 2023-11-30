/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:29:19 by mkong             #+#    #+#             */
/*   Updated: 2023/11/30 19:53:15 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>

void f()
{
	system("leaks a.out");
}

int main()
{
	// atexit(f);
	char	*s;

	int fd = open("abc", O_RDONLY);
	int fds[3];
	fds[0] = open("abc", O_RDONLY);
	fds[1] = open("aa", O_RDONLY);
	fds[2] = open("bb", O_RDONLY);
	// while (1)
	// {
	for (int i = 0; i < 3; ++i)
	{
		s = get_next_line(fds[0]);
		printf("main1  : %s \n", s);
		free(s);
		s = get_next_line(fds[1]);
		printf("main2  : %s \n", s);
		s = get_next_line(fds[1]);
		printf("main2  : %s \n", s);
		free(s);
		s = get_next_line(fds[2]);
		printf("main3  : %s \n", s);
		free(s);
	}
}

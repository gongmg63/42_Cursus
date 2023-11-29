/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:29:19 by mkong             #+#    #+#             */
/*   Updated: 2023/11/29 21:55:49 by mkong            ###   ########.fr       */
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

	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		printf("main  : %s \n", s);
		free(s);
		// s = get_next_line(fd);
		// printf("main  : %s \n", s);
		// free(s);
		// system("leaks a.out");
	}
}

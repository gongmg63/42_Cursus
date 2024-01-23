/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:29:44 by mkong             #+#    #+#             */
/*   Updated: 2024/01/23 17:00:19 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc(char *delimeter)
{
	int		fd;
	char	*s;

	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check_fail(fd);
	check_fail(write(1, "here_doc>", 9));
	s = get_next_line(0);
	if (s == 0)
		error_exit(0);
	while (ft_strncmp(s, delimeter, ft_strlen(delimeter)) != 0)
	{
		check_fail(write(1, "here_doc>", 9));
		check_fail(write(fd, s, ft_strlen(s)));
		free(s);
		s = get_next_line(0);
		if (s == 0)
			error_exit(0);
	}
	free(s);
	return (fd);
}

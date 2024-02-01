/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:29:44 by mkong             #+#    #+#             */
/*   Updated: 2024/02/01 18:57:25 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc(char *delimeter)
{
	int		fd;
	char	*s;

	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check_fail(fd);
	while (1)
	{
		check_fail(write(1, "here_doc>", 9));
		s = get_next_line(0);
		if (ft_strncmp(s, delimeter, ft_strlen(s) - 1) == 0
			&& ft_strncmp(s, delimeter, ft_strlen(delimeter)) == 0)
		{
			free(s);
			return (fd);
		}
		check_fail(write(fd, s, ft_strlen(s)));
		free(s);
		if (s == 0)
			error_exit(0);
	}
	return (fd);
}

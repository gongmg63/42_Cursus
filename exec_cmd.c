/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:06:47 by mkong             #+#    #+#             */
/*   Updated: 2024/01/18 20:05:57 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redir_infile_stdin(t_info *info)
{
	int	fd;

	fd = open(info->infile, O_RDONLY);
	if (fd < 0)
		error_exit();
	if (dup2(fd, 0) == -1)
		error_exit();
}

void	redir_outfile_stdout(t_info *info)
{
	int	fd;

	fd = open(info->outfile, O_WRONLY);
	if (fd < 0)
		error_exit();
	if (dup2(fd, 1) == -1)
		error_exit();
}

void	exec_first(t_info *info, char *cmd_path)
{	
	int	fd;

	fork();
	fd = open(info->infile, O_RDONLY);
	if (fd < 0)
		error_exit();
	if (dup2(fd, 0) == -1)
		error_exit();
	if (execve(cmd_path, info->cmd, 0) == -1)
		error_exit();
}

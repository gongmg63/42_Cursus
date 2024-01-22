/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:06:47 by mkong             #+#    #+#             */
/*   Updated: 2024/01/22 19:57:38 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_first(t_info *info, char *cmd_path)
{
	int	fd;

	check_fail(pipe(info->fds));
	info->pid = fork();
	check_fail(info->pid);
	fd = open(info->infile, O_RDONLY);
	check_fail(fd);
	if (info->pid == 0)
	{
		check_fail(close(info->fds[0]));
		check_fail(dup2(fd, 0));
		check_fail(dup2(info->fds[1], 1));
		check_fail(execve(cmd_path, info->cmd, 0));
	}
	else
		check_fail(waitpid(info->pid, NULL, WNOHANG));
	check_fail(close(fd));
}

void	exec_mid(t_info *info, char *cmd_path)
{
	int	fds[2];

	check_fail(pipe(info->fds));
	info->pid = fork();
	check_fail(info->pid);
	if (info->pid == 0)
	{
		check_fail(close(info->fds[1]));
		check_fail(dup2(info->fds[0], 0));
		check_fail(close(info->fds[0]));
		check_fail(dup2(fds[1], 1));
		check_fail(close(fds[1]));
		check_fail(execve(cmd_path, info->cmd, 0));
	}
	else
		check_fail(waitpid(info->pid, NULL, WNOHANG));
	check_fail(close(info->fds[0]));
	check_fail(close(info->fds[1]));
	ft_memcpy(info->fds, fds, sizeof(fds));
}

void	exec_last(t_info *info, char *cmd_path)
{
	int	fd;

	info->pid = fork();
	if (info->pid == -1)
		error_exit();
	fd = open(info->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_exit();
	if (info->pid == 0)
	{
		if (close(info->fds[1]) == -1)
			error_exit();
		if (dup2(fd, 1) == -1 || dup2(info->fds[0], 0))
			error_exit();
		if (execve(cmd_path, info->cmd, 0) == -1)
			error_exit();
	}
	else
		if (waitpid(info->pid, NULL, WNOHANG) == -1)
			error_exit();
	if (close(fd) == -1)
		error_exit();
}

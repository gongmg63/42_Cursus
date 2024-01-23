/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:06:47 by mkong             #+#    #+#             */
/*   Updated: 2024/01/23 12:50:27 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_first(t_info *info, char *cmd_path, char **envp)
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
		check_fail(execve(cmd_path, info->cmd, envp));
	}
	else
		check_fail(waitpid(info->pid, NULL, WNOHANG));
	check_fail(close(fd));
}

void	exec_mid(t_info *info, char *cmd_path, char **envp)
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
		check_fail(execve(cmd_path, info->cmd, envp));
	}
	else
		check_fail(waitpid(info->pid, NULL, WNOHANG));
	check_fail(close(info->fds[0]));
	check_fail(close(info->fds[1]));
	ft_memcpy(info->fds, fds, sizeof(fds));
}

void	exec_last(t_info *info, char *cmd_path, char **envp)
{
	int	fd;

	info->pid = fork();
	check_fail(info->pid);
	fd = open(info->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check_fail(fd);
	if (info->pid == 0)
	{
		check_fail(close(info->fds[1]));
		check_fail(dup2(fd, 1));
		check_fail(dup2(info->fds[0], 0));
		check_fail(execve(cmd_path, info->cmd, envp));
	}
	else
		check_fail(waitpid(info->pid, NULL, WNOHANG));
	check_fail(close(fd));
}

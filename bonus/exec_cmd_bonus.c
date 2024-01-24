/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:06:47 by mkong             #+#    #+#             */
/*   Updated: 2024/01/24 11:37:59 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_first(t_info *info)
{
	int	fd;

	check_fail(pipe(info->fds));
	check_fail(info->pid);
	if (ft_strncmp(info->av[1], "here_doc", ft_strlen(info->av[1])) == 0)
		fd = open(".here_doc", O_RDONLY);
	else
		fd = open(info->infile, O_RDONLY);
	check_fail(fd);
	info->pid = fork();
	if (info->pid == 0)
	{
		check_fail(close(info->fds[0]));
		check_fail(dup2(fd, 0));
		check_fail(dup2(info->fds[1], 1));
		check_fail(execve(info->cmd_path, info->cmd, info->envp));
	}
	else
		check_fail(waitpid(info->pid, NULL, WNOHANG));
	check_fail(close(fd));
}

void	exec_mid(t_info *info)
{
	int	fds[2];

	check_fail(pipe(fds));
	info->pid = fork();
	check_fail(info->pid);
	if (info->pid == 0)
	{
		check_fail(close(info->fds[1]));
		check_fail(dup2(info->fds[0], 0));
		check_fail(close(info->fds[0]));
		check_fail(dup2(fds[1], 1));
		check_fail(close(fds[1]));
		check_fail(execve(info->cmd_path, info->cmd, info->envp));
	}
	else
		check_fail(waitpid(info->pid, NULL, WNOHANG));
	check_fail(close(info->fds[0]));
	check_fail(close(info->fds[1]));
	ft_memcpy(info->fds, fds, sizeof(fds));
}

void	exec_last(t_info *info)
{
	int	fd;

	if (ft_strncmp(info->av[1], "here_doc", ft_strlen(info->av[1])) == 0)
		fd = open(info->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(info->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	info->pid = fork();
	check_fail(info->pid);
	check_fail(fd);
	if (info->pid == 0)
	{
		check_fail(close(info->fds[1]));
		check_fail(dup2(fd, 1));
		check_fail(dup2(info->fds[0], 0));
		check_fail(execve(info->cmd_path, info->cmd, info->envp));
	}
	else
		check_fail(waitpid(info->pid, NULL, WNOHANG));
	check_fail(close(fd));
}

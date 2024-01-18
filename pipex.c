/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:47:55 by mkong             #+#    #+#             */
/*   Updated: 2024/01/18 19:51:46 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(void)
{
	write(2, "Error!! : ", 10);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(errno);
}

char	**make_path(char *envp[])
{
	char	**path;

	path = NULL;
	while (*envp != 0)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = ft_split(*envp + 5, ':');
			break ;
		}
		envp++;
	}
	return (path);
}

char	*find_path(t_info *info)
{
	int		i;
	char	*path_cmd;
	char	*check_cmd;

	i = -1;
	if (ft_strchr(info->cmd[0], '/'))
	{
		check_cmd = ft_strdup(info->cmd[0]);
		return (check_cmd);
	}
	path_cmd = ft_strjoin("/", info->cmd[0]);
	while (info->path[++i] != 0)
	{
		check_cmd = ft_strjoin(info->path[i], path_cmd);
		if (access(check_cmd, F_OK) == 0)
		{
			free(path_cmd);
			return (check_cmd);
		}
		free(check_cmd);
	}
	error_exit();
	return (0);
}

t_info	*info_initialize(int ac, char *av[], char *envp[])
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	info->path = make_path(envp);
	info->infile = ft_strdup(av[1]);
	info->outfile = ft_strdup(av[ac - 1]);
	info->cmd = NULL;
	if (info == 0 || info->infile == 0 || info->path == 0 || info->outfile == 0)
		error_exit();
	return (info);
}

int	main(int ac, char *av[], char *envp[])
{
	t_info	*info;
	char	*cmd_path;
	int		i;

	// if (ac < 5)
	// 	exit(1);
	info = info_initialize(ac, av, envp);
	i = 1;
	while (++i < ac)
	{
		info->cmd = ft_split(av[i], ' ');
		cmd_path = find_path(info);
		if (info->cmd == 0 || cmd_path == 0)
			error_exit();
		if (i == 2)
			exec_first(info, cmd_path);
	}
	if (execve(cmd_path, info->cmd, 0) == -1)
		error_exit();
	return (0);
}

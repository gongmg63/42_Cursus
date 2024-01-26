/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:39:37 by mkong             #+#    #+#             */
/*   Updated: 2024/01/26 14:27:14 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_exit(char *s)
{
	check_fail(write(2, "Error : ", 8));
	if (s == 0)
		check_fail(write(2, strerror(errno), ft_strlen(strerror(errno))));
	else
	{
		check_fail(write(2, s, ft_strlen(s)));
		if (ft_strncmp(s, "command not found", 17) == 0)
		{
			check_fail(write(2, "\n", 1));
			exit(127);
		}
	}
	check_fail(write(2, "\n", 1));
	if (errno != 0)
		exit(errno);
	else
		exit(1);
}

void	check_fail(int n)
{
	if (n == -1)
		error_exit(0);
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
	check_cmd = ft_strndup("CnF", 3);
	return (check_cmd);
}

t_info	*info_initialize(int ac, char *av[], char *envp[])
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	info->child = 0;
	info->av = av;
	info->envp = envp;
	info->path = make_path(envp);
	info->infile = ft_strdup(av[1]);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) != 0
		&& access(info->infile, F_OK) != 0)
		error_exit(0);
	info->outfile = ft_strdup(av[ac - 1]);
	info->cmd = NULL;
	if (info == 0 || info->infile == 0 || info->path == 0 || info->outfile == 0)
		error_exit(0);
	return (info);
}

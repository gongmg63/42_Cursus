/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:47:55 by mkong             #+#    #+#             */
/*   Updated: 2024/01/22 17:29:18 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_t_d(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i] != 0)
		free(cmd[i]);
	free(cmd);
}

static void	free_info(t_info *info)
{
	free_t_d(info->path);
	free(info->infile);
	free(info->outfile);
	free(info);
}

int	main(int ac, char *av[], char *envp[])
{
	t_info	*info;
	char	*cmd_path;
	int		i;

	if (ac < 5)
		exit(1);
	info = info_initialize(ac, av, envp);
	i = 1;
	while (++i < ac - 1)
	{
		info->cmd = ft_split(av[i], ' ');
		cmd_path = find_path(info);
		if (info->cmd == 0 || cmd_path == 0)
			error_exit();
		if (i == 2)
			exec_first(info, cmd_path);
		else if (i == ac - 2)
			exec_last(info, cmd_path);
		free_t_d(info->cmd);
		free(cmd_path);
	}
	free_info(info);
	return (0);
}

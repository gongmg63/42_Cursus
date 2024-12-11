/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:33:08 by mkong             #+#    #+#             */
/*   Updated: 2024/02/01 19:27:29 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static char	**make_cmd(char *av)
{
	char	**cmd;
	char	sep;
	int		i;

	sep = ' ';
	i = 0;
	if (ft_strchr(av, '\''))
		sep = '\'';
	else if (ft_strchr(av, '\"'))
		sep = '\"';
	if (sep != ' ')
	{
		cmd = (char **)malloc(sizeof(char *) * 3);
		cmd[i++] = ft_strndup(av, ft_strchr(av, ' ') - av);
		cmd[i++] = ft_strndup(ft_strchr(av, sep) + 1, ft_strrchr(av, sep)
				- ft_strchr(av, sep) - 1);
		cmd[i] = NULL;
	}
	else
		cmd = ft_split(av, sep);
	return (cmd);
}

static void	exec_select(int i, int ac, t_info *info)
{
	if (ft_strncmp(info->av[1], "here_doc", ft_strlen(info->av[1])) == 0
		&& ft_strncmp(info->av[1], "here_doc", 8) == 0
		&& i == 3)
	{
		exec_first(info);
		return ;
	}
	if (i == 2)
		exec_first(info);
	else if (i == ac - 2)
		exec_last(info);
	else
		exec_mid(info);
}

int	main(int ac, char *av[], char *envp[])
{
	t_info	*info;
	int		i;

	if (ac < 5)
		error_exit("Invalid argument count");
	info = info_initialize(ac, av, envp);
	i = 1;
	if (ft_strncmp(av[i], "here_doc", ft_strlen(av[i])) == 0
		&& ft_strncmp(av[1], "here_doc", 8) == 0)
		here_doc(av[++i]);
	while (++i < ac - 1)
	{
		info->cmd = make_cmd(av[i]);
		info->cmd_path = find_path(info);
		if (info->cmd == 0 || info->cmd_path == 0)
			error_exit(0);
		exec_select(i, ac, info);
		free_t_d(info->cmd);
		free(info->cmd_path);
	}
	while ((info->child)-- > 0)
		check_fail(wait(NULL));
	free_info(info);
	return (0);
}

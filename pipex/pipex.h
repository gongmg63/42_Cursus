/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:46:21 by mkong             #+#    #+#             */
/*   Updated: 2024/01/24 20:25:58 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include <stdio.h>

typedef struct s_info
{
	char	**envp;
	char	**av;
	char	**path;
	char	**cmd;
	char	*infile;
	char	*outfile;
	char	*cmd_path;
	pid_t	pid;
	int		fds[2];
	int		child;
}				t_info;

void	error_exit(char *s);
void	check_fail(int n);
char	**make_path(char *envp[]);
char	*find_path(t_info *info);
t_info	*info_initialize(int ac, char *av[], char *envp[]);
void	exec_first(t_info *info);
void	exec_last(t_info *info);

#endif

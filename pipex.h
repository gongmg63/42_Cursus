/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:46:21 by mkong             #+#    #+#             */
/*   Updated: 2024/01/18 19:21:23 by mkong            ###   ########.fr       */
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
# include <stdio.h>

typedef struct s_info
{
	char	**path;
	char	**cmd;
	char	*infile;
	char	*outfile;
}				t_info;

void	error_exit(void);
void	exec_first(t_info *info, char *cmd_path);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:55 by mkong             #+#    #+#             */
/*   Updated: 2023/11/30 15:09:00 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
//stdio.h 지우기
char	*get_next_line(int fd);
size_t	check_nl(char *buf);
size_t	ft_strlen(const char *s);
char	*ft_strnjoin(char *s1, char const *s2, size_t n);
char	*ft_strndup(const char *s1, size_t n);

typedef struct s_list
{
	int				fd;
	char			*str;
	size_t			idx;
	ssize_t			r_bytes;
	struct s_list	*next_node;
}				t_list;

#endif

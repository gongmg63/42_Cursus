/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:47 by mkong             #+#    #+#             */
/*   Updated: 2023/11/27 21:09:17 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*free_lst(t_list **lst, char *r_str, int fail)
{
	if (*lst != 0)
	{
		if ((*lst)->str != 0)
			free((*lst)->str);
		(*lst)->str = 0;
		(*lst)->idx = 0;
		if (fail)
		{
			free(*lst);
			*lst = 0;
		}
	}
	if (r_str != 0)
		free(r_str);
	return (0);
}

char	*dup_or_join(t_list *lst, char *r_str, size_t n)
{
	if (r_str == 0)
		r_str = ft_strndup(lst->str + lst->idx, n);
	else
		r_str = ft_strnjoin(r_str, lst->str + lst->idx, n);
	if (r_str == 0)
		return (free_lst(&lst, r_str, 1));
	lst->idx += check_nl(lst->str + lst->idx);
	return (r_str);
}

char	*str_make(t_list *lst, char *r_str)
{
	while (!check_nl(lst->str + lst->idx) && lst->r_bytes != 0)
	{
		r_str = dup_or_join(lst, r_str, BUFFER_SIZE - lst->idx);
		if (r_str == 0)
			return (0);
		free(lst->str);
		lst->str = 0;
		lst->str = (char *)malloc(BUFFER_SIZE + 1);
		if (lst->str == 0)
			return (free_lst(&lst, r_str, 1));
		lst->r_bytes = read(lst->fd, lst->str, BUFFER_SIZE);
		if (lst->r_bytes == -1)
			return (free_lst(&lst, r_str, 1));
		lst->str[lst->r_bytes] = 0;
		lst->idx = 0;
	}
	if (check_nl(lst->str + lst->idx))
	{
		r_str = dup_or_join(lst, r_str, check_nl(lst->str + lst->idx));
		return (r_str);
	}
	if (lst->r_bytes != BUFFER_SIZE)
		r_str = dup_or_join(lst, r_str, lst->r_bytes - lst->idx);
	return (r_str);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*r_str;

	if (fd < 0 || read(fd, 0, 0) == -1)
		return (free_lst(&lst, 0, 1));
	r_str = 0;
	if (lst == 0)
	{
		lst = (t_list *)malloc(sizeof(t_list));
		if (lst == 0)
			return (0);
		lst->idx = 0;
		lst->fd = fd;
		lst->str = 0;
	}
	if (lst->str == 0)
	{
		lst->str = (char *)malloc(BUFFER_SIZE + 1);
		if (lst->str == 0)
			return (free_lst(&lst, r_str, 1));
		lst->r_bytes = read(fd, lst->str, BUFFER_SIZE);
		if (lst->r_bytes == -1)
			return (free_lst(&lst, r_str, 1));
		lst->str[lst->r_bytes] = 0;
	}
	if (lst->str != 0 && lst->r_bytes != 0)
		r_str = str_make(lst, r_str);
	if (lst->str[lst->idx] == 0)
		free_lst(&lst, 0, 0);
	if (lst->r_bytes == 0)
		free_lst(&lst, 0, 1);
	return (r_str);
}

// static char	*malloc_free(char **str, char *buf, char *r_str, size_t *idx)
// {
// 	if (str != 0)
// 	{
// 		free(*str);
// 		*str = 0;
// 	}
// 	free(buf);
// 	free(r_str);
// 	*idx = 0;
// 	return (0);
// }

// char	*get_next_line(int fd)
// {
// 	static char		*str;
// 	static size_t	idx;
// 	char			*r_str;
// 	char			*buf;
// 	ssize_t			r_bytes;

// 	if (fd < 0)
// 		return (0);
// 	r_bytes = BUFFER_SIZE;
// 	r_str = 0;
// 	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (buf == 0)
// 		return (malloc_free(&str, buf, r_str, &idx));
// 	if (str == 0)
// 	{
// 		r_bytes = read(fd, buf, BUFFER_SIZE);
// 		if (r_bytes == -1)
// 			return (malloc_free(0, buf, 0, &idx));
// 		buf[r_bytes] = 0;
// 		str = ft_strndup(buf, r_bytes);
// 		if (str == 0)
// 			return (malloc_free(&str, buf, r_str, &idx));
// 	}
// 	while (!check_nl(str + idx) && r_bytes != 0)
// 	{
// 		if (r_str == 0)
// 			r_str = ft_strndup(str + idx, ft_strlen(str + idx));
// 		else
// 			r_str = ft_strnjoin(r_str, str + idx, ft_strlen(str + idx));
// 		if (r_str == 0)
// 			return (malloc_free(&str, buf, r_str, &idx));
// 		r_bytes = read(fd, buf, BUFFER_SIZE);
// 		if (r_bytes == -1)
// 			return (malloc_free(&str, buf, r_str, &idx));
// 		buf[r_bytes] = 0;
// 		free(str);
// 		str = ft_strndup(buf, r_bytes);
// 		if (str == 0)
// 			return (malloc_free(&str, buf, r_str, &idx));
// 		idx = 0;
// 	}
// 	if (check_nl(str + idx) && r_bytes != 0)
// 	{
// 		if (r_str == 0)
// 			r_str = ft_strndup(str + idx, check_nl(str + idx));
// 		else
// 			r_str = ft_strnjoin(r_str, str + idx, check_nl(str + idx));
// 		if (r_str == 0)
// 			return (malloc_free(&str, buf, r_str, &idx));
// 		idx += check_nl(str + idx);
// 	}
// 	if (r_bytes == 0 || str[idx] == 0)
// 		malloc_free(&str, 0, 0, &idx);
// 	free(buf);
// 	return (r_str);
// }

// static void	is_nl(char	**str, char *buf, char *r_str, size_t *idx, int fd)
// {
// 	ssize_t	r_bytes;

// 	while (!check_nl(*str + *idx) && r_bytes != 0)
// 	{
// 		if (r_str == 0)
// 			r_str = ft_strndup(str + *idx, ft_strlen(str + *idx));
// 		else
// 			r_str = ft_strnjoin(r_str, str + *idx, ft_strlen(str + *idx));
// 		if (r_str == 0)
// 			return (malloc_free(&str, buf, r_str, &idx));
// 		r_bytes = read(fd, buf, BUFFER_SIZE);
// 		if (r_bytes == -1)
// 			return (malloc_free(&str, buf, r_str, &idx));
// 		buf[r_bytes] = 0;
// 		free(str);
// 		str = ft_strndup(buf, r_bytes);
// 		if (str == 0)
// 			return (malloc_free(&str, buf, r_str, &idx));
// 		idx = 0;
// 	}
// }

// static t_list	*allo_node(int fd)
// {
// 	t_list	*lst;

// 	lst = (t_list *)malloc(sizeof(t_list));
// 	if (lst == 0)
// 		return (0);
// 	lst->fd = fd;
// 	lst->idx = 0;
// 	lst->str = 0;
// 	return (lst);
// }

// static char	*malloc_free(t_list **lst, char *buf, char *r_str)
// {
// 	if (*lst != 0)
// 	{
// 		if ((*lst)->str != 0)
// 		{
// 			free((*lst)->str);
// 			(*lst)->str = 0;
// 		}
// 		(*lst)->idx = 0;
// 		free(*lst);
// 		*lst = 0;
// 	}
// 	if (buf != 0)
// 		free(buf);
// 	if (r_str != 0)
// 		free(r_str);
// 	return (0);
// }

// char	*get_next_line(int fd)
// {
// 	static t_list	*lst;
// 	char			*r_str;
// 	char			*buf;
// 	ssize_t			r_bytes;

// 	if (fd < 0)
// 		return (0);
// 	r_bytes = BUFFER_SIZE;
// 	r_str = 0;
// 	lst = allo_node(fd);
// 	if (lst == 0)
// 		return (0);
// 	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (buf == 0)
// 		return (malloc_free(&lst, buf, r_str));
// 	if (lst->str == 0)
// 	{
// 		r_bytes = read(lst->fd, buf, BUFFER_SIZE);
// 		if (r_bytes == -1)
// 			return (malloc_free(&lst, buf, 0));
// 		buf[r_bytes] = 0;
// 		lst->str = ft_strndup(buf, r_bytes);
// 		if (lst->str == 0)
// 			return (malloc_free(&lst, buf, r_str));
// 	}
// 	while (!check_nl(lst->str + lst->idx) && r_bytes != 0)
// 	{
// 		if (r_str == 0)
// 			r_str = ft_strndup(lst->str + lst->idx, ft_strlen(lst->str + lst->idx));
// 		else
// 			r_str = ft_strnjoin(r_str, lst->str + lst->idx, ft_strlen(lst->str + lst->idx));
// 		if (r_str == 0)
// 			return (malloc_free(&lst, buf, r_str));
// 		r_bytes = read(lst->fd, buf, BUFFER_SIZE);
// 		if (r_bytes == -1)
// 			return (malloc_free(&lst, buf, r_str));
// 		buf[r_bytes] = 0;
// 		free(lst->str);
// 		lst->str = ft_strndup(buf, r_bytes);
// 		if (lst->str == 0)
// 			return (malloc_free(&lst, buf, r_str));
// 		lst->idx = 0;
// 	}
// 	if (check_nl(lst->str + lst->idx) && r_bytes != 0)
// 	{
// 		if (r_str == 0)
// 			r_str = ft_strndup(lst->str + lst->idx, check_nl(lst->str + lst->idx));
// 		else
// 			r_str = ft_strnjoin(r_str, lst->str + lst->idx, check_nl(lst->str + lst->idx));
// 		if (r_str == 0)
// 			return (malloc_free(&lst, buf, r_str));
// 		lst->idx += check_nl(lst->str + lst->idx);
// 	}
// 	if (r_bytes == 0 || lst->str[lst->idx] == 0)
// 		malloc_free(&lst, 0, 0);
// 	free(buf);
// 	return (r_str);
// }

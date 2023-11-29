/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:47 by mkong             #+#    #+#             */
/*   Updated: 2023/11/29 22:04:57 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_lst(t_list **lst, char *r_str, int fail)
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

static char	*set_lst(t_list **lst, int fd)
{
	t_list	*new_node;

	new_node = *lst;
	if (*lst == 0)
	{
		*lst = (t_list *)malloc(sizeof(t_list));
		if (*lst == 0)
			return (0);
		(*lst)->fd = fd;
		(*lst)->str = 0;
		(*lst)->next_node = 0;
	}
	else
	{
		while (new_node->next_node && new_node->fd != fd)
			new_node = new_node->next_node;
		if (!new_node->next_node && new_node->fd != fd)
			set_lst(&new_node->next_node, fd);
		if (new_node->fd == fd)
			*lst = new_node;
		else
			*lst = new_node->next_node;
	}
	if ((*lst)->str == 0)
	{
		(*lst)->str = (char *)malloc(BUFFER_SIZE + 1);
		if ((*lst)->str == 0)
			return (free_lst(lst, 0, 1));
		(*lst)->r_bytes = read(fd, (*lst)->str, BUFFER_SIZE);
		if ((*lst)->r_bytes == -1)
			return (free_lst(lst, 0, 1));
		(*lst)->str[(*lst)->r_bytes] = 0;
		(*lst)->idx = 0;
	}
	return ((*lst)->str);
}

static char	*dup_or_join(t_list **lst, char *r_str, size_t n)
{
	if (r_str == 0)
		r_str = ft_strndup((*lst)->str + (*lst)->idx, n);
	else
		r_str = ft_strnjoin(r_str, (*lst)->str + (*lst)->idx, n);
	if (r_str == 0)
		return (free_lst(lst, r_str, 1));
	(*lst)->idx += check_nl((*lst)->str + (*lst)->idx);
	return (r_str);
}

static char	*str_make(t_list **lst, char *r_str)
{
	while (!check_nl((*lst)->str + (*lst)->idx) && (*lst)->r_bytes != 0)
	{
		if ((*lst)->r_bytes == BUFFER_SIZE)
			r_str = dup_or_join(lst, r_str, BUFFER_SIZE - (*lst)->idx);
		else
			r_str = dup_or_join(lst, r_str, (*lst)->r_bytes - (*lst)->idx);
		if (r_str == 0)
			return (free_lst(lst, r_str, 1));
		free((*lst)->str);
		(*lst)->str = 0;
		if (!set_lst(lst, (*lst)->fd))
		{
			free(r_str);
			return (0);
		}
	}
	if (check_nl((*lst)->str + (*lst)->idx))
	{
		r_str = dup_or_join(lst, r_str, check_nl((*lst)->str + (*lst)->idx));
		return (r_str);
	}
	if ((*lst)->r_bytes != BUFFER_SIZE)
		r_str = dup_or_join(lst, r_str, (*lst)->r_bytes - (*lst)->idx);
	return (r_str);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*temp;
	char			*r_str;

	temp = head;
	if (fd < 0 || read(fd, 0, 0) == -1)
	{
		//while (temp)
		return (free_lst(&temp, 0, 1));
	}
	r_str = 0;
	if (!set_lst(&temp, fd))
		return (0);
	if (temp->str != 0 && temp->r_bytes != 0)
		r_str = str_make(&temp, r_str);
	if (temp != 0 && temp->str[temp->idx] == 0)
		free_lst(&temp, 0, (temp->r_bytes < BUFFER_SIZE));
	if (!head)
		head = temp;
	return (r_str);
}

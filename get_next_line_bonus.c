/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:47 by mkong             #+#    #+#             */
/*   Updated: 2023/11/30 19:59:19 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_lst(t_list **lst, t_list *head, char *r_str, int fail)
{
	if (*lst != 0)
	{

		if ((*lst)->str != 0)
			free((*lst)->str);
		(*lst)->str = 0;
		(*lst)->idx = 0;
		if (fail)
		{
			while (head->next_node && *lst != head->next_node)
				head = head->next_node;
			head->next_node = (*lst)->next_node;
			free(*lst);
			*lst = 0;
		}
	}
	if (r_str != 0)
		free(r_str);
	return (0);
}

static char	*set_lst(t_list **lst, t_list *h, int fd)
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
		{
			set_lst(&new_node->next_node, h, fd);
		}
		if (new_node->fd == fd)
			*lst = new_node;
		else
			*lst = new_node->next_node;
	}
	if ((*lst)->str == 0)
	{
		(*lst)->str = (char *)malloc(BUFFER_SIZE + 1);
		if ((*lst)->str == 0)
			return (free_lst(lst, h, 0, 1));
		(*lst)->r_bytes = read(fd, (*lst)->str, BUFFER_SIZE);
		if ((*lst)->r_bytes == -1)
			return (free_lst(lst, h, 0, 1));
		(*lst)->str[(*lst)->r_bytes] = 0;
		(*lst)->idx = 0;
	}
	return ((*lst)->str);
}

static char	*dup_or_join(t_list **lst, t_list *head, char *r_str, size_t n)
{
	if (r_str == 0)
		r_str = ft_strndup((*lst)->str + (*lst)->idx, n);
	else
		r_str = ft_strnjoin(r_str, (*lst)->str + (*lst)->idx, n);
	if (r_str == 0)
		return (free_lst(lst, head, r_str, 1));
	(*lst)->idx += check_nl((*lst)->str + (*lst)->idx);
	return (r_str);
}

static char	*str_make(t_list **lst, t_list *h, char *r_str)
{
	while (!check_nl((*lst)->str + (*lst)->idx) && (*lst)->r_bytes != 0)
	{
		if ((*lst)->r_bytes == BUFFER_SIZE)
			r_str = dup_or_join(lst, h, r_str, BUFFER_SIZE - (*lst)->idx);
		else
			r_str = dup_or_join(lst, h, r_str, (*lst)->r_bytes - (*lst)->idx);
		if (r_str == 0)
			return (free_lst(lst, h, r_str, 1));
		free((*lst)->str);
		(*lst)->str = 0;
		if (!set_lst(lst, h, (*lst)->fd))
		{
			free(r_str);
			return (0);
		}
	}
	if (check_nl((*lst)->str + (*lst)->idx))
	{
		r_str = dup_or_join(lst, h, r_str, check_nl((*lst)->str + (*lst)->idx));
		return (r_str);
	}
	if ((*lst)->r_bytes != BUFFER_SIZE)
		r_str = dup_or_join(lst, h, r_str, (*lst)->r_bytes - (*lst)->idx);
	return (r_str);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_list			*head;
	char			*r_str;
	int				is_one_node;

	head = lst;
	is_one_node = 0;
	if (fd < 0 || read(fd, 0, 0) == -1)
		return (free_lst(&lst, head, 0, 1));
	r_str = 0;
	if (!set_lst(&lst, head, fd))
		return (0);
	if (head == 0)
		head = lst;
	if (head->next_node == 0)
		is_one_node = 1;
	if (lst->str != 0 && lst->r_bytes != 0)
		r_str = str_make(&lst, head, r_str);
	if (lst != 0 && lst->str[lst->idx] == 0)
		free_lst(&lst, head, 0, (lst->r_bytes == 0));
	if ((lst != 0 && is_one_node == 0))
		lst = head;
	return (r_str);
}

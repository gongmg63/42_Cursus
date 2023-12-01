/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:47 by mkong             #+#    #+#             */
/*   Updated: 2023/12/01 21:27:40 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	read_file(t_node_ *head)
{
	ssize_t	rbytes;

	rbytes = BUFFER_SIZE;
	if (head->buf == 0)
	{
		head->buf = (char *)malloc(BUFFER_SIZE + 1);
		if (head->buf == 0)
			return (-1);
		rbytes = read(head->fd, head->buf, BUFFER_SIZE);
		head->idx = 0;
		if (rbytes == -1)
		{
			free(head->buf);
			head->buf = 0;
			head->idx = 0;
			return (rbytes);
		}
		head->buf[rbytes] = 0;
	}
	return (rbytes);
}

t_node_	*set_node_(t_list *lst, int fd, ssize_t *rbytes, t_node_ *head)
{
	t_node_	*prev;

	prev = lst->head;
	while (head != 0 && head->fd != fd)
		head = head->rnode;
	if (head == 0)
	{
		head = (t_node_ *)malloc(sizeof(t_node_));
		if (head == 0)
			return (0);
		head->fd = fd;
		head->buf = 0;
		head->idx = 0;
		head->rnode = 0;
		if (lst->head == 0)
			lst->head = head;
		else
		{
			while (prev->rnode != 0)
				prev = prev->rnode;
			prev->rnode = head;
		}
	}
	*rbytes = read_file(head);
	return (head);
}

char	*make_str(t_node_ *h, ssize_t *rbytes)
{
	char	*str;

	str = 0;
	while (!check_nl(h->buf + h->idx) && (*rbytes > 0))
	{
		if (str == 0)
			str = ft_strndup(h->buf + h->idx, ft_strlen(h->buf + h->idx));
		else
			str = ft_strnjoin(str, h->buf, *rbytes);
		if (str == 0)
			return (0);
		h->idx = 0;
		free(h->buf);
		h->buf = 0;
		*rbytes = read_file(h);
	}
	if ((*rbytes > 0) && check_nl(h->buf + h->idx))
	{
		if (str == 0)
			str = ft_strndup(h->buf + h->idx, check_nl(h->buf + h->idx));
		else
			str = ft_strnjoin(str, h->buf, check_nl(h->buf));
		h->idx += check_nl(h->buf + h->idx);
	}
	return (str);
}

char	*free_lst(t_list *lst, t_node_ *head, char *str, ssize_t rbytes)
{
	t_node_	*temp;

	if (!head)
		return (0);
	free(head->buf);
	head->buf = 0;
	head->idx = 0;
	if (rbytes <= 0)
	{
		if (lst->head == head)
			lst->head = head->rnode;
		else
		{
			temp = lst->head;
			while (temp->rnode != head)
				temp = temp->rnode;
			temp->rnode = head->rnode;
		}
		free(head);
	}
	free(str);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	lst;
	t_node_			*head;
	char			*str;
	ssize_t			rbytes;

	str = 0;
	if (fd < 0)
		return (free_lst(&lst, 0, 0, -1));
	head = set_node_(&lst, fd, &rbytes, lst.head);
	if (head == 0)
		return (0);
	str = make_str(head, &rbytes);
	if (rbytes == -1)
		return (free_lst(&lst, head, str, rbytes));
	if (str == 0)
		return (free_lst(&lst, head, str, 0));
	if (head->buf[head->idx] == 0 || rbytes == 0)
		free_lst(&lst, head, 0, rbytes);
	return (str);
}

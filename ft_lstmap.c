/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:43:14 by mkong             #+#    #+#             */
/*   Updated: 2023/10/25 16:54:02 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	check_malloc(t_list *f_lst, t_list *p_node, void (*del)(void *))
{
	t_list	*next_node;

	if (p_node != 0)
		return (0);
	while (f_lst)
	{
		next_node = f_lst->next;
		(*del)(f_lst->content);
		free(f_lst);
		f_lst = next_node;
	}
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p_node;
	t_list	*f_node;

	f_node = p_node;
	if (lst == 0)
		return (0);
	while (lst)
	{
		p_node = (t_list *)malloc(sizeof(t_list));
		if (check_malloc(&f_node, p_node, (*del)))
			return (0);
		p_node->content = (void *)malloc(sizeof(void *));
		if (check_malloc(f_node, p_node, (*del)))
			return (0);
		p_node->content = (*f)(lst->content);
		p_node = p_node->next;
		lst = lst->next;
	}
	p_node = 0;
	return (f_node);
}

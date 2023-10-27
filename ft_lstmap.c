/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:43:14 by mkong             #+#    #+#             */
/*   Updated: 2023/10/27 17:39:11 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p_node;
	t_list	*f_node;

	if (lst == 0)
		return (0);
	p_node = ft_lstnew((*f)(lst->content));
	if (p_node == 0)
		return (0);
	f_node = p_node;
	while (lst->next)
	{
		lst = lst->next;
		p_node->next = ft_lstnew((*f)(lst->content));
		if (p_node->next == 0)
		{
			ft_lstclear(&f_node, (*del));
			return (0);
		}
		p_node = p_node->next;
	}
	p_node->next = 0;
	return (f_node);
}

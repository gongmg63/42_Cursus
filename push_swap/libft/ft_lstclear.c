/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:27:23 by mkong             #+#    #+#             */
/*   Updated: 2024/01/03 15:41:38 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev_node;

	if (lst == 0)
		return ;
	while (*lst)
	{
		prev_node = *lst;
		(*lst) = (*lst)->next;
		(*del)(prev_node->content);
		free(prev_node);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:40:33 by mkong             #+#    #+#             */
/*   Updated: 2024/01/03 15:41:35 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (lst == 0)
		return ;
	node = *lst;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	if (new)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
}

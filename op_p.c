/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:15:20 by mkong             #+#    #+#             */
/*   Updated: 2024/01/08 16:18:09 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_deque *da, t_deque *db)
{
	if (db->size == 0)
		return ;
	push_front(da, db->data[db->head]);
	pop_front(db);
	ft_printf("pa\n");
}

void	pb(t_deque *da, t_deque *db)
{
	if (da->size == 0)
		return ;
	push_front(db, da->data[da->head]);
	pop_front(da);
	ft_printf("pb\n");
}

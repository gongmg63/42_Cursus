/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:15:24 by mkong             #+#    #+#             */
/*   Updated: 2024/01/08 16:45:10 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_deque *deq)
{
	if (deq->size < 2)
		return ;
	push_front(deq, deq->data[deq->tail]);
	pop_back(deq);
	ft_printf("rra\n");
}

void	rrb(t_deque *deq)
{
	if (deq->size < 2)
		return ;
	push_front(deq, deq->data[deq->tail]);
	pop_back(deq);
	ft_printf("rrb\n");
}

void	rrr(t_deque *da, t_deque *db)
{
	if (da->size < 2 && db->size < 2)
		return ;
	push_front(da, da->data[da->tail]);
	pop_back(da);
	push_front(db, db->data[db->tail]);
	pop_back(db);
	ft_printf("rrr\n");
}

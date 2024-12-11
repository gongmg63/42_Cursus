/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_r.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:15:22 by mkong             #+#    #+#             */
/*   Updated: 2024/01/08 16:20:52 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_deque *deq)
{
	if (deq->size < 2)
		return ;
	push_back(deq, deq->data[deq->head]);
	pop_front(deq);
	ft_printf("ra\n");
}

void	rb(t_deque *deq)
{
	if (deq->size < 2)
		return ;
	push_back(deq, deq->data[deq->head]);
	pop_front(deq);
	ft_printf("rb\n");
}

void	rr(t_deque *da, t_deque *db)
{
	if (da->size < 2 && db->size < 2)
		return ;
	push_back(da, da->data[da->head]);
	pop_front(da);
	push_back(db, db->data[db->head]);
	pop_front(db);
	ft_printf("rr\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:54:41 by mkong             #+#    #+#             */
/*   Updated: 2024/01/08 16:01:52 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pab(t_deque *d1, t_deque *d2, char a_b)
{
	if (d2->size == 0)
		return ;
	push_front(d1, d2->data[d2->head]);
	pop_front(d2);
	if (a_b == 'a')
		ft_printf("pa\n");
	else
		ft_printf("pb\n");
}

void	rab(t_deque *deq, char a_b)
{
	if (deq->size < 2)
		return ;
	push_back(deq, deq->data[deq->head]);
	pop_front(deq);
	if (a_b == 'a')
		ft_printf("ra\n");
	else
		ft_printf("rb\n");
}

void	sab(t_deque *deq, char a_b)
{
	int	tmp;
	int	next_idx;

	if (deq->size <= 1)
		return ;
	if (deq->head == deq->capacity - 1)
		next_idx = 0;
	else
		next_idx = deq->head + 1;
	tmp = deq->data[deq->head];
	deq->data[deq->head] = deq->data[next_idx];
	deq->data[next_idx] = tmp;
	if (a_b == 'a')
		ft_printf("sa\n");
	else
		ft_printf("sb\n");
}

void	rrab(t_deque *deq, char a_b)
{
	if (deq->size < 2)
		return ;
	push_front(deq, deq->data[deq->tail]);
	pop_back(deq);
	if (a_b == 'a')
		ft_printf("rra\n");
	else
		ft_printf("rrb\n");
}

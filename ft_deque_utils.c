/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:11:09 by mkong             #+#    #+#             */
/*   Updated: 2024/01/03 15:16:57 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pop_front(t_deque *deq)
{
	if (deq->size == 0)
		return ;
	if (deq->size == 1)
	{
		deq->head = -1;
		deq->tail = -1;
	}
	else if (deq->head == deq->capacity - 1)
		deq->head = 0;
	else
		++deq->head;
	--deq->size;
}

void	pop_back(t_deque *deq)
{
	if (deq->size == 0)
		return ;
	if (deq->size == 1)
	{
		deq->head = -1;
		deq->tail = -1;
	}
	else if (deq->tail == 0)
		deq->tail = deq->capacity - 1;
	else
		--deq->tail;
	--deq->size;
}

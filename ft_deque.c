/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:39:52 by mkong             #+#    #+#             */
/*   Updated: 2024/01/03 15:17:03 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	initalize(t_deque *deq)
{
	deq->data = NULL;
	deq->size = 0;
	deq->capacity = 0;
	deq->head = -1;
	deq->tail = -1;
}

void	re_allocate(t_deque *deq, int capacity)
{
	int	*new_data;
	int	tmp_tail;
	int	tmp_head;

	if (capacity == 0)
		capacity = 1;
	new_data = (int *)malloc(capacity * sizeof(int));
	tmp_tail = deq->tail + 1;
	tmp_head = deq->head + capacity / 2;
	while (--tmp_tail >= 0)
		new_data[tmp_tail] = deq->data[tmp_tail];
	if (deq->head > deq->tail)
	{
		while (deq->capacity - tmp_head > 0)
		{
			new_data[tmp_head] = deq->data[tmp_head - capacity / 2];
			tmp_head++;
		}
		deq->head = deq->head + capacity / 2;
	}
	free(deq->data);
	deq->data = new_data;
	deq->capacity = capacity;
}

void	push_back(t_deque *deq, int data)
{
	if (deq->size == deq->capacity)
		re_allocate(deq, deq->capacity * 2);
	if (deq->head == -1)
	{
		deq->head = 0;
		deq->tail = 0;
	}
	else if (deq->tail == deq->capacity - 1)
		deq->tail = 0;
	else
		++deq->tail;
	deq->data[deq->tail] = data;
	++deq->size;
}

void	push_front(t_deque *deq, int data)
{
	if (deq->size == deq->capacity)
		re_allocate(deq, deq->capacity * 2);
	if (deq->head == -1)
	{
		deq->head = 0;
		deq->tail = 0;
	}
	else if (deq->head == 0)
		deq->head = deq->capacity - 1;
	else
		--deq->head;
	deq->data[deq->head] = data;
	++deq->size;
}

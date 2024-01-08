/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:15:25 by mkong             #+#    #+#             */
/*   Updated: 2024/01/08 16:34:01 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_deque *deq)
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
	ft_printf("sa\n");
}

void	sb(t_deque *deq)
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
	ft_printf("sb\n");
}

void	ss(t_deque *da, t_deque *db)
{
	int	tmp;
	int	next_idx;

	if (da->size <= 1 && db->size <= 1)
		return ;
	if (da->head == da->capacity - 1)
		next_idx = 0;
	else
		next_idx = da->head + 1;
	tmp = da->data[da->head];
	da->data[da->head] = da->data[next_idx];
	da->data[next_idx] = tmp;
	if (db->head == db->capacity - 1)
		next_idx = 0;
	else
		next_idx = db->head + 1;
	tmp = db->data[db->head];
	db->data[db->head] = db->data[next_idx];
	db->data[next_idx] = tmp;
	ft_printf("ss\n");
}

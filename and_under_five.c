/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_under_five.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:02:47 by mkong             #+#    #+#             */
/*   Updated: 2024/01/05 20:39:43 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_max(t_deque *deq)
{
	int	max;
	int	size;
	int	tmp_head;

	max = deq->data[deq->head];
	size = deq->size;
	tmp_head = deq->head;
	while (size > 0)
	{
		if (max < deq->data[tmp_head])
			max = deq->data[tmp_head];
		tmp_head++;
		size--;
		if (tmp_head == deq->capacity)
			tmp_head = 0;
	}
	return (max);
}

void	ele_two(t_deque *deq, char a_b)
{
	if (check_sort(deq))
		return ;
	sab(deq, a_b);
}

void	ele_three(t_deque *deq, char a_b)
{
	int	f;
	int	s;

	if (check_sort(deq))
		return ;
	f = deq->data[deq->head];
	s = deq->data[deq->head + 1];
	if ((f == 0 && s == 2) || (f == 1 && s == 0) || (f == 2 && s == 1))
		sab(deq, a_b);
	if (deq->data[deq->head] == 1)
		rra(deq);
	else if (deq->data[deq->head] == 2)
		rab(deq, 'a');
}

void	ele_four(t_deque *da, t_deque *db)
{
	if (check_sort(da))
		return ;
	while (da->data[da->head] != 3)
		rab(da, 'a');
	pab(db, da, 'b');
	ele_three(da, 'a');
	pab(da, db, 'a');
	rab(da, 'a');
}

void	ele_five(t_deque *da, t_deque *db)
{
	while (db->size != 2)
	{
		if (da->data[da->head] == 3 || da->data[da->head] == 4)
			pab(db, da, 'b');
		else
			rab(da, 'a');
	}
	ele_three(da, 'a');
	ele_two(db, 'b');
	while (db->size > 0)
	{
		pab(da, db, 'a');
		rab(da, 'a');
	}
}

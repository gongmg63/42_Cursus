/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_under_five.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:02:47 by mkong             #+#    #+#             */
/*   Updated: 2024/01/05 16:48:05 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_sort(t_deque *deq)
{
	int	idx;
	int	*data;

	if (deq->size < 2)
		return (1);
	data = copy_data(deq);
	if (data == 0)
		exit(1);
	idx = 0;
	while (idx < deq->size - 1)
	{
		if (data[idx] > data[idx + 1])
			return (0);
		idx++;
	}
	free (data);
	return (1);
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
		sad(deq, a_b);
	if (deq->data[deq->head] == 1)
		rra(deq);
	else if (deq->data[deq->head == 2])
		ra(deq, a_b);
}

void	ele_four(t_deque *da, t_deque *db)
{
	while (da->data[da->head] != 3)
		rab(da, 'a');
	pab(db, da, 'b');
	ele_three(da, 'a');
	pab(da, db, 'a');
	ra(da, 'a');
}

void	ele_five(t_deque *da, t_deque *db)
{
	while (db->size != 2)
	{
		if (da->data[da->head] == 3 || da->data[da->head] == 4)
			pab(db, da, 'b');
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


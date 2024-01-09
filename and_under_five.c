/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_under_five.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:02:47 by mkong             #+#    #+#             */
/*   Updated: 2024/01/09 13:40:45 by mkong            ###   ########.fr       */
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
	if (a_b == 'a')
		sa(deq);
	else
		sb(deq);
}

void	ele_three(t_deque *deq)
{
	int	f;
	int	s;

	if (check_sort(deq))
		return ;
	f = deq->data[deq->head];
	s = deq->data[deq->head + 1];
	if ((f == 0 && s == 2) || (f == 1 && s == 0) || (f == 2 && s == 1))
		sa(deq);
	if (deq->data[deq->head] == 1)
		rra(deq);
	else if (deq->data[deq->head] == 2)
		ra(deq);
}

void	ele_four(t_deque *da, t_deque *db)
{
	if (check_sort(da))
		return ;
	while (da->data[da->head] != 3)
		ra(da);
	pb(da, db);
	ele_three(da);
	pa(da, db);
	ra(da);
}

void	ele_five(t_deque *da, t_deque *db)
{
	while (db->size != 2)
	{
		if (da->data[da->head] == 3 || da->data[da->head] == 4)
			pb(da, db);
		else
			ra(da);
	}
	ele_three(da);
	ele_two(db, 'b');
	while (db->size > 0)
	{
		pa(da, db);
		ra(da);
	}
}

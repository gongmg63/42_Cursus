/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:48:02 by mkong             #+#    #+#             */
/*   Updated: 2024/01/04 15:58:32 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_sort(t_deque *deq, int input_num)
{
	int	tmp_tail;
	int	tmp_head;

	if (input_num != deq->size)
		return (0);
	tmp_tail = deq->tail;
	tmp_head = deq->head + 1;
	while (tmp_tail >= tmp_head)
	{
		if (deq->data[tmp_tail] < deq->data[tmp_tail - 1])
			return (0);
		tmp_tail--;
	}
	if (tmp_tail < tmp_head)
	{
		while (deq->capacity - tmp_head > 0)
		{
			if (deq->data[tmp_head] < deq->data[tmp_head - 1])
				return (0);
			tmp_head++;
		}
		if (deq->data[tmp_head] > deq->data[0])
			return (0);
	}
	return (1);
}

static void	bit_sort(t_deque *d1, t_deque *d2, int bit, char a_b)
{
	int	size;

	size = d1->size;
	while (d1->size > 0)
	{
		if ((d1->data[d1->head] >> bit) / 2 == 0)
		{
			pab(d2, d1, a_b - 1);
			if (d2->size > 0)
				rab(d2, a_b - 1);
		}
		else
			rab(d1, a_b);
		size--;
	}
}

static int	check_max_bit(t_deque *deq)
{
	int	max;
	int	bit;
	int	tmp_head;
	int	size;

	max = 0;
	bit = 1;
	tmp_head = deq->head;
	size = deq->size;
	while (size > 0)
	{
		if (max < deq->data[tmp_head])
			max = deq->data[tmp_head];
		tmp_head++;
		size--;
		if (tmp_head == deq->capacity)
			tmp_head = 0;
	}
	while (max > 0)
	{
		bit++;
		max /= 2;
	}
	return (bit);
}

void	radix_sort(t_deque *da, t_deque *db)
{
	int	input_num;
	int	bit;
	int	max_bit;

	input_num = da->size;
	bit = 0;
	max_bit = check_max_bit(da);
	bit_sort(da, db, bit++, 'a');
	while (bit < max_bit)
	{
		bit_sort(da, db, bit, 'a');
		bit_sort(db, da, bit, 'b');
		bit++;
	}
	while (db->size > 0)
		pab(da, db, 'a');
}

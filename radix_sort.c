/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:48:02 by mkong             #+#    #+#             */
/*   Updated: 2024/01/04 21:34:43 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// static int	check_sort(t_deque *deq, int input_num)
// {
// 	int	tmp_tail;
// 	int	tmp_head;

// 	if (input_num != deq->size)
// 		return (0);
// 	tmp_tail = deq->tail;
// 	tmp_head = deq->head + 1;
// 	while (tmp_tail >= tmp_head)
// 	{
// 		if (deq->data[tmp_tail] < deq->data[tmp_tail - 1])
// 			return (0);
// 		tmp_tail--;
// 	}
// 	if (tmp_tail < tmp_head)
// 	{
// 		while (deq->capacity - tmp_head > 0)
// 		{
// 			if (deq->data[tmp_head] < deq->data[tmp_head - 1])
// 				return (0);
// 			tmp_head++;
// 		}
// 		if (deq->data[tmp_head] > deq->data[0])
// 			return (0);
// 	}
// 	return (1);
// }
void	deq_print(t_deque *deq)
{
	int	tmp_head;
	int	size;

	tmp_head = deq->head;
	size = deq->size;
	while (size > 0)
	{
		ft_printf("result : %d ", deq->data[tmp_head]);
		tmp_head++;
		size--;
		if (tmp_head == deq->capacity)
			tmp_head = 0;
	}
	ft_printf("\n");
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

static void	bit_sort(t_deque *d1, t_deque *d2, int bit, char a_b, int first)
{
	int	size;

	size = d1->size;
	while (size > 0)
	{
		if ((d1->data[d1->head] >> bit) % 2 == 0 && a_b == 'a')
		{
			pab(d2, d1, a_b - 1);
			if (first)
				rab(d2, a_b - 1);
		}
		else if ((d1->data[d1->head] >> bit) % 2 == 1 && a_b == 'b')
		{
			pab(d2, d1, a_b - 1);
			if (first)
				rab(d2, a_b - 1);
		}
		else
			rab(d1, a_b);
		size--;
	}
}

void	radix_sort(t_deque *da, t_deque *db)
{
	int	input_num;
	int	bit;
	int	max_bit;

	input_num = da->size;
	bit = 0;
	max_bit = check_max_bit(da);
	bit_sort(da, db, bit++, 'a', 0);
	deq_print(db);
	while (bit < max_bit)
	{
		bit_sort(da, db, bit, 'a', 1);
		ft_printf("da : ");
		deq_print(db);
		bit_sort(db, da, bit, 'b', 1);
		ft_printf("db : ");
		deq_print(db);
		bit++;
	}
	while (db->size > 0)
		pab(da, db, 'a');
	deq_print(da);
}

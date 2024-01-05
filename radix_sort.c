/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:48:02 by mkong             #+#    #+#             */
/*   Updated: 2024/01/05 15:03:01 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	bit = 0;
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

static void	bit_sort(t_deque *da, t_deque *db, int bit)
{
	int	size;

	size = da->size;
	while (size > 0)
	{
		if ((da->data[da->head] >> bit) % 2 == 0)
			pab(db, da, 'b');
		else
			rab(da, 'a');
		size--;
	}
	while (db->size > 0)
		pab(da, db, 'a');
}

void	radix_sort(t_deque *da, t_deque *db)
{
	int	input_num;
	int	bit;
	int	max_bit;

	input_num = da->size;
	bit = 0;
	max_bit = check_max_bit(da);
	while (bit < max_bit)
		bit_sort(da, db, bit++);
}

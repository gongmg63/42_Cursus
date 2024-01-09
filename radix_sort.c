/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:48:02 by mkong             #+#    #+#             */
/*   Updated: 2024/01/09 17:11:07 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
			pb(da, db);
		else
			ra(da);
		size--;
	}
	while (db->size > 0)
		pa(da, db);
}

int	check_sort(t_deque *deq)
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
		{
			free(data);
			return (0);
		}
		idx++;
	}
	free (data);
	return (1);
}

void	radix_sort(t_deque *da, t_deque *db)
{
	int	bit;
	int	max_bit;

	bit = 0;
	max_bit = check_max_bit(da);
	while (bit < max_bit)
		bit_sort(da, db, bit++);
}


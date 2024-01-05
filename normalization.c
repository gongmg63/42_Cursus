/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:38:10 by mkong             #+#    #+#             */
/*   Updated: 2024/01/05 15:29:54 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*copy_data(t_deque *deq)
{
	int	i;
	int	*data;
	int	tmp_head;
	int	size;

	size = deq->size;
	tmp_head = deq->head;
	data = (int *)malloc(sizeof(int) * deq->size);
	if (data == 0)
		exit(1);
	i = 0;
	while (size > 0)
	{
		data[i] = deq->data[tmp_head];
		tmp_head++;
		i++;
		size--;
		if (tmp_head == deq->capacity)
			tmp_head = 0;
	}
	return (data);
}

void	normalization(t_deque *deq)
{
	int	i;
	int	j;
	int	*data;

	data = copy_data(deq);
	ft_memset(deq->data, 0, deq->size * sizeof(int));
	i = 0;
	while (i < deq->size)
	{
		j = 0;
		while (j < deq->size)
		{
			if (data[i] > data[j])
				++deq->data[i];
			j++;
		}
		i++;
	}
	deq->head = 0;
	deq->tail = deq->size - 1;
}

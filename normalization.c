/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:38:10 by mkong             #+#    #+#             */
/*   Updated: 2024/01/09 14:11:28 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_exit(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	two_d_free(char **words, int idx)
{
	while (idx >= 0)
	{
		free(words[idx]);
		idx--;
	}
	free(words);
}

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
		error_exit();
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
	free(data);
	deq->head = 0;
	deq->tail = deq->size - 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:34:56 by mkong             #+#    #+#             */
/*   Updated: 2024/01/05 20:23:54 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	check_dup(t_deque *deq, int n)
{
	int	tmp_head;
	int	size;

	tmp_head = deq->head;
	size = deq->size - 1;
	while (size > 0)
	{
		if (deq->data[tmp_head] == n)
		{
			ft_printf("Error\n");
			exit(1);
		}
		tmp_head++;
		size--;
		if (tmp_head == deq->capacity)
			tmp_head = 0;
	}
}

static void	insert_arg(t_deque *deq, int ac, char **av)
{
	char	**strs;
	int		av_idx;
	int		s_idx;

	av_idx = 1;
	while (av_idx < ac)
	{
		s_idx = 0;
		strs = ft_split(av[av_idx], ' ');
		if (strs == 0)
		{
			ft_printf("Error\n");
			exit(1);
		}
		while (strs[s_idx] != 0)
		{
			push_back(deq, ft_atoi(strs[s_idx]));
			check_dup(deq, deq->data[deq->tail]);
			s_idx++;
		}
		two_dimension_free(strs, s_idx - 1);
		av_idx++;
	}
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
			return (0);
		idx++;
	}
	free (data);
	return (1);
}

int	main(int ac, char *av[])
{
	t_deque	*da;
	t_deque	*db;

	da = (t_deque *)malloc(sizeof(t_deque));
	db = (t_deque *)malloc(sizeof(t_deque));
	initalize(da);
	initalize(db);
	insert_arg(da, ac, av);
	normalization(da);
	if (check_sort(da))
		exit(0);
	if (da->size == 2)
		ele_two(da, 'a');
	if (da->size == 3)
		ele_three(da, 'a');
	if (da->size == 4)
		ele_four(da, db);
	if (da->size == 5)
		ele_five(da, db);
	if (da->size > 5)
		radix_sort(da, db);
	deq_print(da);
	exit(0);
}

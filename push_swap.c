/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:34:56 by mkong             #+#    #+#             */
/*   Updated: 2024/01/08 16:42:33 by mkong            ###   ########.fr       */
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

static void	free_deq(t_deque *deq)
{
	free(deq->data);
	free(deq);
}

static void	sort_div(t_deque *da, t_deque *db)
{
	if (!check_sort(da))
	{
		if (da->size == 2)
			ele_two(da, 'a');
		if (da->size == 3)
			ele_three(da);
		if (da->size == 4)
			ele_four(da, db);
		if (da->size == 5)
			ele_five(da, db);
		if (da->size > 5)
			radix_sort(da, db);
	}
}

int	main(int ac, char *av[])
{
	t_deque	*da;
	t_deque	*db;

	da = (t_deque *)malloc(sizeof(t_deque));
	if (da == 0)
		return (0);
	db = (t_deque *)malloc(sizeof(t_deque));
	if (db == 0)
	{
		free_deq(da);
		return (0);
	}
	initalize(da);
	initalize(db);
	insert_arg(da, ac, av);
	normalization(da);
	sort_div(da, db);
	free_deq(da);
	free_deq(db);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:34:56 by mkong             #+#    #+#             */
/*   Updated: 2024/01/05 16:56:06 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
			s_idx++;
		}
		two_dimension_free(strs, s_idx - 1);
		av_idx++;
	}
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
	exit(0);
}

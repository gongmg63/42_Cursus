/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:34:56 by mkong             #+#    #+#             */
/*   Updated: 2024/01/04 15:04:02 by mkong            ###   ########.fr       */
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
	t_deque	*deq_a;
	t_deque	*deq_b;
	int		input_num;

	deq_a = (t_deque *)malloc(sizeof(t_deque));
	initalize(deq_a);
	initalize(deq_b);
	insert_arg(deq_a, ac, av);
	input_num = deq_a->size;
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:34:56 by mkong             #+#    #+#             */
/*   Updated: 2024/01/03 16:48:11 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	insert_arg(t_deque *deq, int ac, char **av)
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
			push_back(deq, ft_atoi(strs[s_idx++]));
		two_dimension_free(strs, s_idx - 1);
	}
}

int	main(int ac, char *av[])
{
	char	**strs;
	t_deque	*deq;

	initalize(deq);
	insert_arg(deq, ac, av);
	for (int i = 0;i < ac - 1; ++i)
	{
		ft_printf("%d\n", deq->data[i]);
	}
	exit(0);
}

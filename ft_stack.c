/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:00:16 by mkong             #+#    #+#             */
/*   Updated: 2024/01/12 20:51:04 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize(t_stack *st)
{
	st->size = 0;
	st->top = 0;
}

void	push(t_stack *st, t_point p)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == 0)
	{
		write(2, "Error : Malloc Fail\n", 20);
		exit(1);
	}
	node->p = p;
	node->next_node = 0;
	if (st->top == 0)
	{
		st->size = 1;
		st->top = node;
	}
	else
	{
		node->next_node = st->top;
		st->top = node;
		st->size++;
	}
}

t_point	pop(t_stack *st)
{
	t_node	*tmp;
	t_point	p;

	if (st->size == 0)
		return ((t_point){-1, -1});
	tmp = st->top;
	p = st->top->p;
	st->top = st->top->next_node;
	st->size--;
	free(tmp);
	return (p);
}

void	clear_st(t_stack *st)
{
	while (st->top != 0)
		pop(st);
}

int	find_node(t_stack *st, t_point p)
{
	t_node	*tmp;

	tmp = st->top;
	while (tmp != 0)
	{
		if (tmp->p.x == p.x && tmp->p.y == p.y)
			return (1);
		tmp = tmp->next_node;
	}
	return (0);
}

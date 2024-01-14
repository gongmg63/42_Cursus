/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:00:16 by mkong             #+#    #+#             */
/*   Updated: 2024/01/14 16:42:04 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize(t_stack *st)
{
	st->top = NULL;
	st->size = 0;
}

void	push(t_stack *st, t_point p)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == 0)
		exit(1);
	node->p = (t_point){p.x, p.y};
	node->next_node = NULL;
	if (st->top == NULL)
		st->top = node;
	else
	{
		node->next_node = st->top;
		st->top = node;
	}
	st->size++;
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
	while (tmp != NULL)
	{
		if (tmp->p.x == p.x && tmp->p.y == p.y)
			return (1);
		tmp = tmp->next_node;
	}
	return (0);
}

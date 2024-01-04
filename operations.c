/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:54:41 by mkong             #+#    #+#             */
/*   Updated: 2024/01/04 20:50:45 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pab(t_deque *d1, t_deque *d2, char a_b)
{
	if (d2->size == 0)
		return ;
	push_front(d1, d2->data[d2->head]);
	pop_front(d2);
	if (a_b == 'a')
		ft_printf("pa\n");
	else
		ft_printf("pb\n");
}

void	rab(t_deque *deq, char a_b)
{
	if (deq->size < 2)
		return ;
	push_back(deq, deq->data[deq->head]);
	pop_front(deq);
	if (a_b == 'a')
		ft_printf("ra\n");
	else
		ft_printf("rb\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:48:44 by mkong             #+#    #+#             */
/*   Updated: 2024/01/08 16:45:54 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct s_deque
{
	int	*data;
	int	size;
	int	capacity;
	int	head;
	int	tail;
}	t_deque;

void	initalize(t_deque *deq);
void	re_allocate(t_deque *deq, int capacity);
void	push_back(t_deque *deq, int data);
void	push_front(t_deque *deq, int data);
void	pop_front(t_deque *deq);
void	pop_back(t_deque *deq);
void	radix_sort(t_deque *da, t_deque *db);
void	pab(t_deque *d1, t_deque *d2, char a_b);
void	rab(t_deque *deq, char a_b);
void	normalization(t_deque *deq);
int		*copy_data(t_deque *deq);
void	sab(t_deque *deq, char a_b);
void	rrab(t_deque *deq, char a_b);
void	ele_two(t_deque *deq, char a_b);
void	ele_three(t_deque *deq);
void	ele_four(t_deque *da, t_deque *db);
void	ele_five(t_deque *da, t_deque *db);
int		check_sort(t_deque *deq);
void	sa(t_deque *deq);
void	sb(t_deque *deq);
void	ss(t_deque *da, t_deque *db);
void	pa(t_deque *da, t_deque *db);
void	pb(t_deque *da, t_deque *db);
void	ra(t_deque *deq);
void	rb(t_deque *deq);
void	rr(t_deque *da, t_deque *db);
void	rra(t_deque *deq);
void	rrb(t_deque *deq);
void	rrr(t_deque *da, t_deque *db);

#endif

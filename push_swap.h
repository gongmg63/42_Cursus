/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:48:44 by mkong             #+#    #+#             */
/*   Updated: 2024/01/04 15:59:25 by mkong            ###   ########.fr       */
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

#endif

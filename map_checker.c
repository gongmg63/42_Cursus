/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:19:08 by mkong             #+#    #+#             */
/*   Updated: 2024/01/12 14:20:07 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./mlx/mlx.h"

t_stack	*check_map_route(char **map, t_stack *st)
{
	t_point		present;
	t_point		next;
	t_stack		*visit;
	int			idx;
	const int	dxy[2][4] = {{1, 0, -1, 0}, {0, 1, 0, -1}};

	present = find_start(map);
	push(st, present);
	initialize(visit);
	push(visit, present);
	while (st->size != 0)
	{
		present = pop(st);
		idx = -1;
		while (++idx < 4)
		{
			next.x = present.x + dxy[0][idx];
			next.y = present.y + dxy[1][idx];
			if (map[next.x, next.y] == '1' || find_node(visit, next))
				continue ;
			push(visit, next);
			push(st, next);
		}
	}
	return (visit);
}

int	check_map_valid(char **map, t_stack *visit, int count[3])
{
	t_point	p;

	while (visit->size > 0)
	{
		p = pop(visit);
		if (check_element(map[p.x][p.y] < 4))
			count[check_element(map[p.x][p.y]) - 1]--;
	}
	if (count[0] != 0 && count[1] != 0 && count[2] != 0)
		return (0);
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:19:08 by mkong             #+#    #+#             */
/*   Updated: 2024/01/14 17:51:39 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./mlx/mlx.h"

static void	check_map_route(char **map, t_stack *st, t_stack *visit)
{
	t_point		present;
	t_point		next;
	int			i;
	const int	dxy[2][4] = {{1, 0, -1, 0}, {0, 1, 0, -1}};

	push(st, find_start(map));
	push(visit, find_start(map));
	while (st->size != 0)
	{
		present = pop(st);
		i = -1;
		while (++i < 4)
		{
			next.x = present.x + dxy[0][i];
			next.y = present.y + dxy[1][i];
			if (map[next.x][next.y] == '1' || find_node(visit, next))
				continue ;
			push(visit, next);
			push(st, next);
		}
	}
}

static int	check_map_valid(char **map, t_stack *visit, int count[3])
{
	t_point	p;

	while (visit->size > 0)
	{
		p = pop(visit);
		if (check_element(map[p.x][p.y]) < 4)
			count[check_element(map[p.x][p.y]) - 1]--;
	}
	if (count[0] == 0 && count[1] == 0 && count[2] == 0)
		return (1);
	return (0);
}

static void	call_valid_element(char **map)
{
	t_stack	*st;
	t_stack	*visit;
	int		count[3];

	check_map_element(map, count);
	st = (t_stack *)malloc(sizeof(t_stack));
	visit = (t_stack *)malloc(sizeof(t_stack));
	if (st == 0 || visit == 0)
		exit(1);
	initialize(st);
	initialize(visit);
	check_map_route(map, st, visit);
	if (count[0] == 0)
	{
		write(2, "Error : Map's element is wrong.\n", 33);
		exit(1);
	}
	else if (check_map_valid(map, visit, count) == 0)
	{
		write(2, "Error : Route isn't valid.\n", 28);
		exit(1);
	}
	clear_st(st);
	clear_st(visit);
}

int	check_map(char **map)
{
	t_point	hw;
	int		count[3];

	hw = check_h_w(map);
	if (check_edge(map) == 0)
	{
		write(2, "Error : Edge must be wall.\n", 28);
		exit(1);
	}
	else if (hw.x == 0)
	{
		write(2, "Error : Map isn't rectangle.\n", 30);
		exit(1);
	}
	call_valid_element(map);
	check_map_element(map, count);
	return (count[2]);
}

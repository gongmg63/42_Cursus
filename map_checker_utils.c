/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:39:28 by mkong             #+#    #+#             */
/*   Updated: 2024/01/12 14:10:22 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_element(char c)
{
	if (c == 'C')
		return (3);
	if (c == 'E')
		return (2);
	if (c == 'P')
		return (1);
	if (c == '0' || c == '1')
		return (5);
	return (0);
}

int	check_edge(char **map)
{
	int	idx;
	int	jdx;

	idx = 0;
	while (map[idx] != 0)
	{
		jdx = 0;
		while (map[idx][jdx] != 0)
		{
			if ((idx == 0 || map + sizeof(char *) == 0) && map[idx][jdx] != 1)
				return (0);
			else
			{
				if ((jdx == 0 || map[idx][jdx + 1] == 0) && map[idx][jdx] != 1)
					return (0);
			}
			jdx++;
		}
		idx++;
	}
	return (1);
}

int	*check_map_element(char **map)
{
	int		idx;
	int		count[3];

	idx = 0;
	ft_memset(count, 0, sizeof(int) * 3);
	while (map[idx] != 0)
	{
		while (*map[idx] != 0)
		{
			if (check_element(*map[idx]) == 0)
				return (0);
			else
				if (check_element(*map[idx]) < 4)
					count[check_element(*map[idx] - 1)]++;
			map[idx]++;
		}
		idx++;
	}
	if (count[0] != 1 && count[1] != 1 && count[2] < 1)
		return (0);
	return (count);
}

t_point	check_h_w(char **map)
{
	t_point	hw;
	int		idx;
	int		tmp;

	idx = 0;
	while (map[idx] != 0)
	{
		tmp = 0;
		while (*map[idx] != 0)
		{
			if (idx == 0)
				hw.x++;
			tmp++;
			map[idx]++;
		}
		if (hw.x != tmp)
		{
			hw.x = 0;
			return ((t_point){0, 0});
		}
	}
	hw.y = idx;
	return (hw);
}

t_point	find_start(char **map)
{
	t_point	start;
	int		idx;
	int		jdx;

	while (map[idx] != 0)
	{
		while (map[idx][jdx] != 0)
		{
			if (map[idx][jdx] == 'P')
			{
				start.x = jdx;
				start.y = idx;
				return (start);
			}
			jdx++;
		}
		idx++;
	}
	return (start);
}

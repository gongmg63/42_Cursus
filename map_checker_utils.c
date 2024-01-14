/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:39:28 by mkong             #+#    #+#             */
/*   Updated: 2024/01/14 15:44:33 by mkong            ###   ########.fr       */
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

t_point	find_start(char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i] != 0)
	{
		j = -1;
		while (map[i][++j] != 0)
		{
			if (map[i][j] == 'P')
				return ((t_point){i, j});
		}
	}
	return ((t_point){0, 0});
}

int	check_edge(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i] != 0)
	{
		j = -1;
		while (map[i][++j] != 0)
		{
			if ((i == 0 || map[i + 1] == 0) && map[i][j] != '1')
				return (0);
			else
			{
				if ((j == 0 || map[i][j + 1] == 0) && map[i][j] != '1')
					return (0);
			}
		}
	}
	return (1);
}

t_point	check_h_w(char **map)
{
	t_point	hw;
	int		i;
	int		j;
	int		tmp;

	i = -1;
	hw.x = 0;
	while (map[++i] != 0)
	{
		tmp = 0;
		j = -1;
		while (map[i][++j] != 0)
		{
			if (i == 0)
				hw.x++;
			tmp++;
		}
		if (hw.x != tmp)
		{
			hw.x = 0;
			return ((t_point){0, 0});
		}
	}
	hw.y = i;
	return (hw);
}

void	check_map_element(char **map, int count[3])
{
	int	i;
	int	j;

	i = -1;
	ft_memset(count, 0, sizeof(int) * 3);
	while (map[++i] != 0)
	{
		j = -1;
		while (map[i][++j] != 0)
		{
			if (check_element(map[i][j]) == 0)
			{
				ft_bzero(count, sizeof(int) * 3);
				return ;
			}
			else
				if (check_element(map[i][j]) < 4)
					count[check_element(map[i][j]) - 1]++;
		}
	}
	if (count[0] != 1 && count[1] != 1 && count[2] < 1)
		ft_bzero(count, sizeof(int) * 3);
}

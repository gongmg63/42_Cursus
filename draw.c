/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:10:31 by mkong             #+#    #+#             */
/*   Updated: 2024/04/12 18:20:34 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_grid(t_info info, int size)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = -1;
		while (++i < size)
		{
			my_mlx_pixel_put(&info.data, j, i, 0xFF0000);
			my_mlx_pixel_put(&info.data, i, j, 0xFF0000);
		}
		j += 100;
	}
}

void	draw_rectangle(t_info info, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			my_mlx_pixel_put(&info.data, x + i, y + j, color);
		}
	}
}

void	draw_map(t_info info)
{
	int	i;
	int j;

	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
		{
			if (info.map[i][j] == '1')
				draw_rectangle(info, j * 100, i * 100, 100, 0xFFFFFF);
			else
				draw_rectangle(info, j * 100, i * 100, 100, 0x000000);
		}
	}
	draw_grid(info, 1000);
}

void	draw_user(t_info *info, int x, int y)
{
	int	i;
	int	j;

	if (x != -1 || y != -1)
	{
		draw_rectangle(*info, info->pos_x * 100, info->pos_y * 100, 10, 0x0000FF);
		return ;
	}
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
		{
			if (info->map[i][j] == 'N' || info->map[i][j] == 'E' || info->map[i][j] == 'W' || info->map[i][j] == 'S')
			{
				draw_rectangle(*info, j * 100 + 45, i * 100 + 45, 10, 0x0000FF);
				info->pos_x = j + 0.45;
				info->pos_y = i + 0.45;
				if (info->map[i][j] == 'N')
				{
					info->dir_x = 0;
					info->dir_y = -1;
				}
				else if (info->map[i][j] == 'S')
				{
					info->dir_x = 0;
					info->dir_y = 1;
				}
				else if (info->map[i][j] == 'E')
				{
					info->dir_x = 1;
					info->dir_y = 0;
				}
				else if (info->map[i][j] == 'W')
				{
					info->dir_x = -1;
					info->dir_y = 0;
				}
			}
		}
	}
}

void	draw_verline(t_info info, int draw_start, int draw_end, int y, int color)
{
	while (draw_start <= draw_end)
	{
		my_mlx_pixel_put(&info.data, y, draw_start, color);
		draw_start++;
	}
}

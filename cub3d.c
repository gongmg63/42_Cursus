/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:18 by mkong             #+#    #+#             */
/*   Updated: 2024/04/09 20:59:07 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char map[10][10] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'} ,
	{'1', '0', '0', '1', '0', '0', '0', '0', '0', '1'} ,
	{'1', '0', '0', '1', '0', '0', '0', '0', '0', '1'} ,
	{'1', '0', '1', '0', '0', '1', '0', '1', '0', '1'} ,
	{'1', '0', '1', '0', '0', '0', '0', '0', '0', '1'} ,
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'} ,
	{'1', '0', '0', '0', '1', '0', 'S', '0', '0', '1'} ,
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'} ,
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'} ,
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'} ,
};

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
			if (map[i][j] == '1')
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
		draw_rectangle(*info, info->pos_X, info->pos_Y, 10, 0x0000FF);
		return ;
	}
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S')
			{
				draw_rectangle(*info, j * 100 + 45, i * 100 + 45, 10, 0x0000FF);
				info->pos_X = j * 100 + 45;
				info->pos_Y = i * 100 + 45;
			}
		}
	}
}

int	exit_window(void)
{
	exit(0);
	return (0);
}

int	key_press(int keycode, t_info *info)
{
	printf("x : %f, y : %f \n", info->pos_X, info->pos_Y);
	if (keycode == KEY_W)
	{
		info->pos_Y--;
	}
	else if (keycode == KEY_A)
	{
		info->pos_X--;
	}
	else if (keycode == KEY_S)
	{
		info->pos_Y++;
	}
	else if (keycode == KEY_D)
	{
		info->pos_X++;
	}
	else if (keycode == KEY_ESC)
		exit(0);
	mlx_destroy_image(info->mlx, info->data.img);
	info->data.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->data.addr = mlx_get_data_addr(info->data.img, &info->data.bits_per_pixel, \
							&info->data.line_length, &info->data.endian);
	draw_map(*info);
	draw_user(info, info->pos_X, info->pos_Y);
	mlx_put_image_to_window(info->mlx, info->win, info->data.img, 0, 0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info info;

	(void)argc;
	(void)argv;
	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "cub3D");
	info.move_speed = 1;
	info.data.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.data.addr = mlx_get_data_addr(info.data.img, &info.data.bits_per_pixel, \
							&info.data.line_length, &info.data.endian);
	// info.map = map;
	draw_map(info);
	draw_user(&info, -1, -1);
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 0, exit_window, 0);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, key_press, &info);
	mlx_put_image_to_window(info.mlx, info.win, info.data.img, 0, 0);
	mlx_loop(info.mlx);
}

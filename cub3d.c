/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:18 by mkong             #+#    #+#             */
/*   Updated: 2024/04/11 21:26:41 by mkong            ###   ########.fr       */
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
	{'1', '0', '0', '0', '1', '0', 'W', '0', '0', '1'} ,
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
		draw_rectangle(*info, info->pos_x, info->pos_y, 10, 0x0000FF);
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
				info->pos_x = j * 100 + 45;
				info->pos_y = i * 100 + 45;
				if (map[i][j] == 'N')
				{
					info->dir_x = 0;
					info->dir_y = -1;
				}
				else if (map[i][j] == 'S')
				{
					info->dir_x = 0;
					info->dir_y = 1;
				}
				else if (map[i][j] == 'E')
				{
					info->dir_x = 1;
					info->dir_y = 0;
				}
				else if (map[i][j] == 'W')
				{
					info->dir_x = -1;
					info->dir_y = 0;
				}
			}
		}
	}
}

int	exit_window(void)
{
	exit(0);
	return (0);
}

int	check_move(int keycode, t_info *info)
{
	printf("x : %f, y : %f \n", info->pos_x, info->pos_y);
	if (map[(int)(info->pos_y / 100)][(int)(info->pos_x / 100)] == '1')
	{
		if (keycode == KEY_W)
			info->pos_y += info->move_speed;
		else if (keycode == KEY_A)
			info->pos_x += info->move_speed;
		else if (keycode == KEY_S)
			info->pos_y -= info->move_speed;
		else if (keycode == KEY_D)
			info->pos_x -= info->move_speed;
		return (0);
	}
	return (1);
}

void	calc_ray(t_info *info)
{
	t_dda	dda;
	int		i;

	i = 0;
	while (i < WIDTH)
	{
		info->camera_x = 2 * i / (double)WIDTH - 1;
		info->raydir_x = info->dir_x + info->plane_x * info->camera_x;
		info->raydir_y = info->dir_y + info->plane_y * info->camera_x;
		dda.map_x = (int)info->pos_x / 100;
		dda.map_y = (int)info->pos_y / 100;
		// printf("map_x : %d , map_y : %d \n", dda.map_x, dda.map_y);
		dda.deltadist_x = fabs(1 / info->raydir_x);
		dda.deltadist_y = fabs(1 / info->raydir_y);
		dda.hit = 0;
		if (info->raydir_x < 0)
		{
			dda.step_x = -1;
			dda.sidedist_x = (info->pos_x / 100 - dda.map_x) * dda.deltadist_x;
		}
		else
		{
			dda.step_x = 1;
			dda.sidedist_x = (dda.map_x + 1 - info->pos_x / 100) * dda.deltadist_x;
		}
		if (info->raydir_y < 0)
		{
			dda.step_y = -1;
			dda.sidedist_y = (info->pos_y / 100 - dda.map_y) * dda.deltadist_y;
		}
		else
		{
			dda.step_y = 1;
			dda.sidedist_y = (dda.map_y + 1 - info->pos_x / 100) * dda.deltadist_y;
		}
		while (!dda.hit)
		{
			if (dda.sidedist_x < dda.sidedist_y)
			{
				dda.sidedist_x += dda.deltadist_x;
				dda.map_x += dda.step_x;
				dda.side = 0;
			}
			else
			{
				dda.sidedist_y += dda.deltadist_y;
				dda.map_y += dda.step_y;
				dda.side = 1;
			}
			if (map[dda.map_x][dda.map_y] == '1')
			{
				dda.hit = 1;
				printf("hit x : %d , hit y : %d \n", dda.map_x, dda.map_y);
			}
		}
		i += 10;
	}
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == KEY_W)
		info->pos_y -= info->move_speed;
	else if (keycode == KEY_A)
		info->pos_x -= info->move_speed;
	else if (keycode == KEY_S)
		info->pos_y += info->move_speed;
	else if (keycode == KEY_D)
		info->pos_x += info->move_speed;
	else if (keycode == KEY_ESC)
		exit(0);
	if (!check_move(keycode, info))
		return (0);
	mlx_destroy_image(info->mlx, info->data.img);
	info->data.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->data.addr = mlx_get_data_addr(info->data.img, &info->data.bits_per_pixel, \
							&info->data.line_length, &info->data.endian);
	draw_map(*info);
	draw_user(info, info->pos_x, info->pos_y);
	calc_ray(info);
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
	info.plane_x = 0;
	info.plane_y = 0.66;
	draw_map(info);
	draw_user(&info, -1, -1);
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 0, exit_window, 0);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, key_press, &info);
	mlx_put_image_to_window(info.mlx, info.win, info.data.img, 0, 0);
	mlx_loop(info.mlx);
}

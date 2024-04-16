/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:12:55 by mkong             #+#    #+#             */
/*   Updated: 2024/04/16 21:22:30 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_window(void)
{
	exit(0);
	return (0);
}

void	rotate_press(int keycode, t_info *info)
{
	double	dir_x;
	double	plane_x;
	double	rotate_speed;

	dir_x = info->dir_x;
	plane_x = info->plane_x;
	if (keycode == KEY_AR_L)
		rotate_speed = info->rotate_speed;
	else
		rotate_speed = -info->rotate_speed;
	info->dir_x = dir_x * cos(rotate_speed) - info->dir_y * sin(rotate_speed);
	info->dir_y = dir_x * sin(rotate_speed) + info->dir_y * cos(rotate_speed);
	info->plane_x = plane_x * cos(rotate_speed) - info->plane_y * sin(rotate_speed);
	info->plane_y = plane_x * sin(rotate_speed) + info->plane_y * cos(rotate_speed);
}

void	set_pos(double *pos_x, double *pos_y, int keycode, t_info *info)
{
	if (keycode == KEY_W)
	{
		*pos_y += info->dir_y * info->move_speed;
		*pos_x += info->dir_x * info->move_speed;
	}
	else if (keycode == KEY_S)
	{
		*pos_y -= info->dir_y * info->move_speed;
		*pos_x -= info->dir_x * info->move_speed;
	}
	else if (keycode == KEY_A)
	{
		*pos_y += info->dir_x * info->move_speed;
		*pos_x -= info->dir_y * info->move_speed;
	}
	else if (keycode == KEY_D)
	{
		*pos_y -= info->dir_x * info->move_speed;
		*pos_x += info->dir_y * info->move_speed;
	}
}

void	move_position(int keycode, t_info *info)
{
	double	pos_x;
	double	pos_y;


	pos_x = info->pos_x;
	pos_y = info->pos_y;
	set_pos(&pos_x, &pos_y, keycode, info);
	if (info->map[(int)(pos_x)][(int)(pos_y + 0.2)] == '1' \
		|| info->map[(int)(pos_x)][(int)(pos_y - 0.2)] == '1'\
		|| info->map[(int)(pos_x + 0.2)][(int)(pos_y)] == '1'\
		|| info->map[(int)(pos_x - 0.2)][(int)(pos_y)] == '1'\
		|| info->map[(int)(pos_x - 0.2)][(int)(pos_y - 0.2)] == '1'\
		|| info->map[(int)(pos_x - 0.2)][(int)(pos_y + 0.2)] == '1'\
		|| info->map[(int)(pos_x + 0.2)][(int)(pos_y - 0.2)] == '1'\
		|| info->map[(int)(pos_x + 0.2)][(int)(pos_y + 0.2)] == '1')
		return ;
	info->pos_x = pos_x;
	info->pos_y = pos_y;
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || keycode == KEY_D)
		move_position(keycode, info);
	else if (keycode == KEY_AR_L || keycode == KEY_AR_R)
		rotate_press(keycode, info);
	else if (keycode == KEY_ESC)
		exit(0);
	mlx_destroy_image(info->mlx, info->data.img);
	info->data.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->data.addr = (int *)mlx_get_data_addr(info->data.img, &info->data.bits_per_pixel, \
							&info->data.line_length, &info->data.endian);
	calc_ray(info);
	mlx_put_image_to_window(info->mlx, info->win, info->data.img, 0, 0);
	return (0);
}

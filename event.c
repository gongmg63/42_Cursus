/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:12:55 by mkong             #+#    #+#             */
/*   Updated: 2024/04/12 15:33:42 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_window(void)
{
	exit(0);
	return (0);
}

int	check_move(int keycode, t_info *info)
{
	// printf("x : %f, y : %f \n", info->pos_x, info->pos_y);
	if (info->map[(int)info->pos_y][(int)info->pos_x] == '1')
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

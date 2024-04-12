/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:18 by mkong             #+#    #+#             */
/*   Updated: 2024/04/12 19:03:14 by mkong            ###   ########.fr       */
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
	{'1', '0', '0', '0', '1', '0', 'N', '0', '0', '1'} ,
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'} ,
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'} ,
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'} ,
};

int	main(int argc, char *argv[])
{
	t_info info;

	(void)argc;
	(void)argv;
	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "cub3D");
	info.move_speed = 0.02;
	info.map = map;
	info.data.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.data.addr = mlx_get_data_addr(info.data.img, &info.data.bits_per_pixel, \
							&info.data.line_length, &info.data.endian);
	// draw_map(info);
	draw_user(&info, -1, -1);
	calc_ray(&info);
	mlx_put_image_to_window(info.mlx, info.win, info.data.img, 0, 0);
	info.plane_x = (info.dir_y * -1) * 0.66;
	info.plane_y = (info.dir_x * -1) * 0.66;
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 0, exit_window, 0);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, key_press, &info);
	mlx_put_image_to_window(info.mlx, info.win, info.data.img, 0, 0);
	mlx_loop(info.mlx);
}

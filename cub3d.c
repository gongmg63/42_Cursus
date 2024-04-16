/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:18 by mkong             #+#    #+#             */
/*   Updated: 2024/04/16 21:01:45 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char map[10][10] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'} ,
	{'1', '1', '0', '1', '0', '0', '0', '0', '0', '1'} ,
	{'1', '0', '0', '1', '0', '0', '0', '0', '0', '1'} ,
	{'1', '0', '1', '0', '0', '1', '0', '0', '0', '1'} ,
	{'1', '0', '1', '0', '0', '0', '0', '0', '0', '1'} ,
	{'1', '0', '0', '0', '0', '0', '0', '0', '1', '1'} ,
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'} ,
	{'1', '0', '0', '0', '1', '0', 'N', '0', '0', '1'} ,
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'} ,
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'} ,
};

void	set_dir_vec(t_info *info)
{
	if (info->map[(int)info->pos_x][(int)info->pos_y] == 'N')
	{
		info->dir_x = -1;
		info->dir_y = 0;
	}
	else if (info->map[(int)info->pos_x][(int)info->pos_y] == 'S')
	{
		info->dir_x = 1;
		info->dir_y = 0;
	}
	else if (info->map[(int)info->pos_x][(int)info->pos_y] == 'E')
	{
		info->dir_x = 0;
		info->dir_y = 1;
	}
	else if (info->map[(int)info->pos_x][(int)info->pos_y] == 'W')
	{
		info->dir_x = 0;
		info->dir_y = -1;
	}
}

void	find_start_point(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
		{
			if (info->map[i][j] == 'N' || info->map[i][j] == 'E' \
				|| info->map[i][j] == 'W' || info->map[i][j] == 'S')
			{
				info->pos_x = i + 0.48;
				info->pos_y = j + 0.48;
				break ;
			}
		}
	}
}

void	image_set(t_info *info, int *texture, char *path, t_data *data)
{
	int	i;
	int	j;
	int	img_width;
	int	img_height;

	data->img = mlx_xpm_file_to_image(info->mlx, path, &img_width, &img_height);
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	i = -1;
	while (++i < img_height)
	{
		j = -1;
		while (++j < img_width)
			texture[img_width * i + j] = data->addr[img_width * i + j];
	}
	mlx_destroy_image(info->mlx, data->img);
}

void	texture_set(t_info *info)
{
	t_data	data;

	image_set(info, info->texture[0], "./textures/bluestone.xpm", &data);
	image_set(info, info->texture[1], "./textures/colorstone.xpm", &data);
	image_set(info, info->texture[2], "./textures/eagle.xpm", &data);
	image_set(info, info->texture[3], "./textures/greystone.xpm", &data);
}

void	set_info(t_info *info)
{
	int	i;

	i = -1;
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			info->buf[i][j] = 0;
		}
	}
	info->mlx = mlx_init();
	info->win =  mlx_new_window(info->mlx, WIDTH, HEIGHT, "cub3D");
	info->texture = (int **)malloc(sizeof(int *) * 4);
	if (info->texture == NULL)
		exit(1);
	while (++i < 4)
	{
		info->texture[i] = malloc(sizeof(int) * TEXTURE_WIDTH * TEXTURE_HEIGHT);
		if (info->texture[i] == NULL)
			exit(1);
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < TEXTURE_HEIGHT * TEXTURE_WIDTH; ++j)
			info->texture[i][j] = 0;
	}
	texture_set(info);
	info->map = map;
	info->data.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->data.addr = (int *)mlx_get_data_addr(info->data.img, &info->data.bits_per_pixel, \
							&info->data.line_length, &info->data.endian);
	find_start_point(info);
	set_dir_vec(info);
	info->re_buf = 0;
	info->plane_x = (info->dir_y * -1) * 0.66;
	info->plane_y = (info->dir_x * -1) * 0.66;
	info->rotate_speed = 0.02;
	info->move_speed = 0.02;
}

int	main(int argc, char *argv[])
{
	t_info info;

	(void)argc;
	(void)argv;
	set_info(&info);
	calc_ray(&info);
	mlx_put_image_to_window(info.mlx, info.win, info.data.img, 0, 0);
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 0, exit_window, 0);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, key_press, &info);
	mlx_put_image_to_window(info.mlx, info.win, info.data.img, 0, 0);
	mlx_loop(info.mlx);
	return (0);
}

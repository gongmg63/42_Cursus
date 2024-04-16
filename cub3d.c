/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:18 by mkong             #+#    #+#             */
/*   Updated: 2024/04/16 17:14:22 by mkong            ###   ########.fr       */
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

void	image_set(t_info *info, int *texture, char *path, t_img *img)
{
	int	i;
	int	j;

	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	i = -1;
	while (++i < img->img_height)
	{
		j = -1;
		while (++j < img->img_width)
			texture[img->img_width * i + j] = img->data[img->img_width * i + j];
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	texture_set(t_info *info)
{
	t_img	img;

	image_set(info, info->texture[0], "textures/bluestone.xpm", &img);
	image_set(info, info->texture[1], "textures/bluestone.xpm", &img);
	image_set(info, info->texture[2], "textures/bluestone.xpm", &img);
	image_set(info, info->texture[3], "textures/bluestone.xpm", &img);
}

void	set_info(t_info *info)
{
	int	i;

	i = -1;
	info->mlx = mlx_init();
	info->win =  mlx_new_window(info->mlx, WIDTH, HEIGHT, "cub3D");
	info->texture = (int **)malloc(sizeof(int *) * 4);
	if (info->texture == NULL)
		exit(1);
	while (++i < 4)
	{
		info->texture[i] = (int *)malloc(sizeof(int) * texture_width * texture_height);
		if (info->texture[i] == NULL)
			exit(1);
	}
	info->map = map;
	info->data.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->data.addr = mlx_get_data_addr(info->data.img, &info->data.bits_per_pixel, \
							&info->data.line_length, &info->data.endian);
	find_start_point(info);
	set_dir_vec(info);
	texture_set(info);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:21:49 by mkong             #+#    #+#             */
/*   Updated: 2024/01/12 21:02:36 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "so_long.h"

int	main(int ac, char *av[])
{
	char	**map;
	void	*mlx;
	void	*win;

	if (ac != 2)
		exit(1);
	mlx = mlx_init();
	map = read_map(av[1]);
	check_map_size(map, mlx, win);
	mlx_loop(mlx);
}

	// void	*mlx;
	// void	*win_ptr;
	// void *img;
	// void *img2;
	// void *img3;
	// void *img4;
	// void *img5;
	// void *img6;
	// void *img7;
	// int img_width;
	// int img_height;

	// mlx = mlx_init();
	// win_ptr = mlx_new_window(mlx, 500, 500, "my_mlx");
	// img = mlx_xpm_file_to_image(mlx, "./img/Stone.xpm", &img_width, &img_height);
	// img2 = mlx_xpm_file_to_image(mlx, "./img/Bush.xpm", &img_width, &img_height);
	// img3 = mlx_xpm_file_to_image(mlx, "./img/Exit_inactive.xpm", &img_width, &img_height);
	// img4 = mlx_xpm_file_to_image(mlx, "./img/Exit_active.xpm", &img_width, &img_height);
	// img5 = mlx_xpm_file_to_image(mlx, "./img/HappySheep.xpm", &img_width, &img_height);
	// img6 = mlx_xpm_file_to_image(mlx, "./img/Meat.xpm", &img_width, &img_height);
	// img7 = mlx_xpm_file_to_image(mlx, "./img/Tile.xpm", &img_width, &img_height);
	// for (int i = 0; i < 500; i += 64)
	// 	for (int j = 0; j < 500; j += 64)
	// 		mlx_put_image_to_window(mlx, win_ptr, img7, i, j);
	// mlx_put_image_to_window(mlx, win_ptr, img, 0, 0);
	// mlx_put_image_to_window(mlx, win_ptr, img2, 64, 0);
	// mlx_put_image_to_window(mlx, win_ptr, img3, 128, 0);
	// mlx_put_image_to_window(mlx, win_ptr, img4, 192, 0);
	// mlx_put_image_to_window(mlx, win_ptr, img5, 0, 64);
	// mlx_put_image_to_window(mlx, win_ptr, img6, 64, 64);
	// mlx_loop(mlx);
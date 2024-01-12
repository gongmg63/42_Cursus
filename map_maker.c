/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:37:12 by mkong             #+#    #+#             */
/*   Updated: 2024/01/12 19:45:49 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./mlx/mlx.h"

void	check_map_size(char **map, void *mlx, void *win)
{
	t_point	hw;
	int		width;
	int		height;
	void	*img;
	int		tmp;

	hw = check_h_w(map);
	if (hw.x <= 130 && hw.y <= 130)
		win = mlx_new_window(mlx, hw.x * 64, hw.y * 64, "so_long");
	else
	{
		write(2, "Error : Map size is too big.\n", 18);
		exit(1);
	}
	img = mlx_xpm_file_to_image(mlx, "./img/Tile.xpm", &width, &height);
	while (--hw.y >= 0)
	{
		tmp = -1;
		while (++tmp < hw.x)
			mlx_put_image_to_window(mlx, win, img, tmp * 64, hw.y * 64);
	}
}

char	**read_map(char *file)
{
	int		fd;
	char	*map;
	char	*line;

	fd = open(file, O_RDONLY);
	map = get_next_line(fd);
	if (map == 0)
		return (0);
	line = get_next_line(fd);
	while (line != 0)
	{
		map = ft_strjoin(map, line);
		if (map == 0)
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (ft_split(map, '\n'));
}

// void	draw_map(char **map, t_mlx *mlx)
// {
// 	void	*img;
// 	int		*img_height;
// 	int		*img_width;
// 	int		idx;

// 	idx = 0;
// 	check_map_size(map, mlx);
// 	while (map[idx] != 0)
// 	{
// 		while (*map[idx] != 0)
// 		{
// 			if ()
// 		}
// 	}
// }

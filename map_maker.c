/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:37:12 by mkong             #+#    #+#             */
/*   Updated: 2024/01/12 16:44:01 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./mlx/mlx.h"

void	check_map_size(char **map, t_mlx *m)
{
	t_point	hw;
	int		*width;
	int		*height;
	void	*img;

	m->mlx = mlx_init();
	hw = check_h_w(map);
	mlx_get_screen_size(m->mlx, width, height);
	if (hw.x * 64 <= *width && hw.y * 64 <= *height)
		m->win = mlx_new_window(m->mlx, hw.y * 64, hw.x * 64, "so_long");
	else
	{
		write(2, "Error : Map Oversize\n", 18);
		exit(1);
	}
	img = mlx_xpm_file_to_image(m->mlx, "./img/Tile.xpm", width, height);
	while (--hw.y >= 0)
		while (--hw.x >= 0)
			mlx_put_image_to_window(m->mlx, m->win, img, hw.x * 64, hw.y * 64);
}

char	**read_map(char *file)
{
	int		fd;
	char	*map;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (line == 0)
		return (0);
	while (line != 0)
	{
		map = ft_strjoin(map, line);
		if (map == 0)
			return (0);
		map = ft_strjoin(map, " ");
		if (map == 0)
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (ft_split(map, ' '));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:37:12 by mkong             #+#    #+#             */
/*   Updated: 2024/01/14 17:59:38 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./mlx/mlx.h"

static void	check_map_size(char **map, t_mlx *m)
{
	t_point	hw;
	int		width;
	int		height;
	void	*img;
	int		tmp;

	hw = check_h_w(map);
	m->mlx = mlx_init();
	if (hw.x <= 130 && hw.y <= 130)
		m->win = mlx_new_window(m->mlx, hw.x * 64, hw.y * 64, "so_long");
	else
	{
		write(2, "Error : Map size is too big.\n", 18);
		exit(1);
	}
	img = mlx_xpm_file_to_image(m->mlx, "./img/Tile.xpm", &width, &height);
	while (--hw.y >= 0)
	{
		tmp = -1;
		while (++tmp < hw.x)
			mlx_put_image_to_window(m->mlx, m->win, img, tmp * 64, hw.y * 64);
	}
}

static void	*check_img(char c, t_mlx *m)
{
	int	w;
	int	h;

	if (c == '1')
		return (mlx_xpm_file_to_image(m->mlx, "./img/Bush.xpm", &w, &h));
	if (c == 'C')
		return (mlx_xpm_file_to_image(m->mlx, "./img/Meat.xpm", &w, &h));
	if (c == 'E')
		return (mlx_xpm_file_to_image(m->mlx, "./img/Exit_inact.xpm", &w, &h));
	if (c == 'P')
		return (mlx_xpm_file_to_image(m->mlx, "./img/HappySheep.xpm", &w, &h));
	return (0);
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

void	draw_map(char **map, t_mlx *m)
{
	void	*img;
	int		i;
	int		j;

	i = -1;
	check_map_size(map, m);
	while (map[++i] != 0)
	{
		j = -1;
		while (map[i][++j] != 0)
		{
			img = check_img(map[i][j], m);
			if (img != 0)
				mlx_put_image_to_window(m->mlx, m->win, img, j * 64, i * 64);
		}
	}
}

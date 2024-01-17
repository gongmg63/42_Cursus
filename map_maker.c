/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:37:12 by mkong             #+#    #+#             */
/*   Updated: 2024/01/17 15:22:59 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(char *s)
{
	write(2, "Error : ", 8);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(1);
}

static void	check_map_size(t_mlx *m)
{
	t_point	hw;
	int		width;
	int		height;
	void	*img;
	int		tmp;

	hw = check_h_w(m->map);
	if (hw.x <= 130 && hw.y <= 130)
		m->win = mlx_new_window(m->mlx, hw.x * 64, hw.y * 64, "so_long");
	else
		error_exit("Map size is too big");
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
	char	**ret;
	char	*line;

	if (ft_strncmp(file + ft_strlen(file) - 4, ".ber", 4) != 0)
		error_exit("Wrong Map's name");
	fd = open(file, O_RDONLY);
	map = get_next_line(fd);
	if (map == 0)
		error_exit("Broken Map");
	line = get_next_line(fd);
	while (line != 0)
	{
		if (ft_strncmp(line, "\n", 1) == 0)
			error_exit("Broken Map");
		map = ft_strjoin(map, line);
		if (map == 0)
			return (0);
		line = get_next_line(fd);
	}
	ret = ft_split(map, '\n');
	free(map);
	return (ret);
}

void	draw_map(t_mlx *m)
{
	void	*img;
	int		i;
	int		j;

	i = -1;
	check_map_size(m);
	while (m->map[++i] != 0)
	{
		j = -1;
		while (m->map[i][++j] != 0)
		{
			img = check_img(m->map[i][j], m);
			if (img != 0)
				mlx_put_image_to_window(m->mlx, m->win, img, j * 64, i * 64);
		}
	}
}

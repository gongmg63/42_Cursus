/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:21:49 by mkong             #+#    #+#             */
/*   Updated: 2024/01/17 15:26:21 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_point	find_exit(char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i] != 0)
	{
		j = -1;
		while (map[i][++j] != 0)
		{
			if (map[i][j] == 'E')
				return ((t_point){i, j});
		}
	}
	return ((t_point){0, 0});
}

static void	active_exit(t_mlx *m)
{
	void	*img;
	int		w;
	int		h;
	t_point	exit;

	exit = find_exit(m->map);
	if (m->collect != 0 || (exit.x == 0 && exit.y == 0))
		return ;
	img = mlx_xpm_file_to_image(m->mlx, "./img/Exit_act.xpm", &w, &h);
	mlx_put_image_to_window(m->mlx, m->win, img, exit.y * 64, exit.x * 64);
	m->map[exit.x][exit.y] = 'e';
}

static int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
	{
		mlx->p.x--;
		move_w(mlx);
	}
	else if (keycode == KEY_A)
	{
		mlx->p.y--;
		move_a(mlx);
	}
	else if (keycode == KEY_S)
	{
		mlx->p.x++;
		move_s(mlx);
	}
	else if (keycode == KEY_D)
	{
		mlx->p.y++;
		move_d(mlx);
	}
	else if (keycode == KEY_ESC)
		exit(0);
	active_exit(mlx);
	return (0);
}

static int	exit_window(void)
{
	exit(0);
	return (0);
}

int	main(int ac, char *av[])
{
	t_mlx		*mlx;

	if (ac != 2)
		error_exit("Wrong argument");
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (mlx == 0)
		error_exit("Malloc error");
	mlx->cnt = 0;
	mlx->mlx = mlx_init();
	mlx->map = read_map(av[1]);
	mlx->collect = check_map(mlx->map);
	mlx->p = find_start(mlx->map);
	draw_map(mlx);
	mlx_hook(mlx->win, 2, 0, key_press, mlx);
	mlx_hook(mlx->win, 17, 0, exit_window, 0);
	mlx_loop(mlx);
	return (0);
}

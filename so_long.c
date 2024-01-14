/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:21:49 by mkong             #+#    #+#             */
/*   Updated: 2024/01/14 17:58:53 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "so_long.h"

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
		mlx->p.y--;
		// move_w(mlx);
	else if (keycode == KEY_A)
		mlx->p.x--;
	else if (keycode == KEY_S)
		mlx->p.y--;
	else if (keycode == KEY_D)
		mlx->p.x++;
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	main(int ac, char *av[])
{
	t_mlx	*mlx;
	int		count;

	if (ac != 2)
		exit(1);
	count = 0;
	mlx = (t_mlx *)malloc(sizeof(mlx));
	if (mlx == 0)
		exit(1);
	mlx->map = read_map(av[1]);
	mlx->collect = check_map(mlx->map);
	mlx->p = find_start(mlx->map);
	draw_map(mlx->map, mlx);
	printf("%s \n", mlx->map[1]);
	mlx_key_hook(mlx->win, key_press, mlx);
	count++;
	write(1, &count, 4);
	write(1, "\n", 1);
	mlx_loop(mlx);
	exit(0);
}

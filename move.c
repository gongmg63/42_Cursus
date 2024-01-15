/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:20:09 by mkong             #+#    #+#             */
/*   Updated: 2024/01/15 13:19:54 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "so_long.h"

void	move_w(t_mlx *m)
{
	void	*img;
	int		w;
	int		h;

	if (m->map[m->p.x][m->p.y] == '1')
	{
		m->p.x++;
		return ;
	}
	if (m->map[m->p.x][m->p.y] == 'e')
		exit(0);
	if (m->map[m->p.x + 1][m->p.y] == 'E')
		img = mlx_xpm_file_to_image(m->mlx, "./img/Exit_inact.xpm", &w, &h);
	else
		img = mlx_xpm_file_to_image(m->mlx, "./img/Tile.xpm", &w, &h);
	mlx_put_image_to_window(m->mlx, m->win, img, m->p.y * 64, m->p.x * 64 + 64);
	img = mlx_xpm_file_to_image(m->mlx, "./img/HappySheep.xpm", &w, &h);
	mlx_put_image_to_window(m->mlx, m->win, img, m->p.y * 64, m->p.x * 64);
	if (m->map[m->p.x][m->p.y] == 'C' && m->collect > 0)
	{
		m->collect--;
		m->map[m->p.x][m->p.y] = 'c';
	}
	m->cnt++;
	ft_printf("%d\n", m->cnt);
}

void	move_a(t_mlx *m)
{
	void	*img;
	int		w;
	int		h;

	if (m->map[m->p.x][m->p.y] == '1')
	{
		m->p.y++;
		return ;
	}
	if (m->map[m->p.x][m->p.y] == 'e')
		exit(0);
	if (m->map[m->p.x][m->p.y + 1] == 'E')
		img = mlx_xpm_file_to_image(m->mlx, "./img/Exit_inact.xpm", &w, &h);
	else
		img = mlx_xpm_file_to_image(m->mlx, "./img/Tile.xpm", &w, &h);
	mlx_put_image_to_window(m->mlx, m->win, img, m->p.y * 64 + 64, m->p.x * 64);
	img = mlx_xpm_file_to_image(m->mlx, "./img/HappySheep.xpm", &w, &h);
	mlx_put_image_to_window(m->mlx, m->win, img, m->p.y * 64, m->p.x * 64);
	if (m->map[m->p.x][m->p.y] == 'C' && m->collect > 0)
	{
		m->collect--;
		m->map[m->p.x][m->p.y] = 'c';
	}
	m->cnt++;
	ft_printf("%d\n", m->cnt);
}

void	move_s(t_mlx *m)
{
	void	*img;
	int		w;
	int		h;

	if (m->map[m->p.x][m->p.y] == '1' || m->map[m->p.x][m->p.y] == 'E')
	{
		m->p.x--;
		return ;
	}
	if (m->map[m->p.x][m->p.y] == 'e')
		exit(0);
	if (m->map[m->p.x - 1][m->p.y] == 'E')
		img = mlx_xpm_file_to_image(m->mlx, "./img/Exit_inact.xpm", &w, &h);
	else
		img = mlx_xpm_file_to_image(m->mlx, "./img/Tile.xpm", &w, &h);
	mlx_put_image_to_window(m->mlx, m->win, img, m->p.y * 64, m->p.x * 64 - 64);
	img = mlx_xpm_file_to_image(m->mlx, "./img/HappySheep.xpm", &w, &h);
	mlx_put_image_to_window(m->mlx, m->win, img, m->p.y * 64, m->p.x * 64);
	if (m->map[m->p.x][m->p.y] == 'C' && m->collect > 0)
	{
		m->collect--;
		m->map[m->p.x][m->p.y] = 'c';
	}
	m->cnt++;
	ft_printf("%d\n", m->cnt);
}

void	move_d(t_mlx *m)
{
	void	*img;
	int		w;
	int		h;

	if (m->map[m->p.x][m->p.y] == '1' || m->map[m->p.x][m->p.y] == 'E')
	{
		m->p.y--;
		return ;
	}
	if (m->map[m->p.x][m->p.y] == 'e')
		exit(0);
	if (m->map[m->p.x][m->p.y - 1] == 'E')
		img = mlx_xpm_file_to_image(m->mlx, "./img/Exit_inact.xpm", &w, &h);
	else
		img = mlx_xpm_file_to_image(m->mlx, "./img/Tile.xpm", &w, &h);
	mlx_put_image_to_window(m->mlx, m->win, img, m->p.y * 64 - 64, m->p.x * 64);
	img = mlx_xpm_file_to_image(m->mlx, "./img/HappySheep.xpm", &w, &h);
	mlx_put_image_to_window(m->mlx, m->win, img, m->p.y * 64, m->p.x * 64);
	if (m->map[m->p.x][m->p.y] == 'C' && m->collect > 0)
	{
		m->collect--;
		m->map[m->p.x][m->p.y] = 'c';
	}
	m->cnt++;
	ft_printf("%d\n", m->cnt);
}

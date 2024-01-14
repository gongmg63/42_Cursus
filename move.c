/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:20:09 by mkong             #+#    #+#             */
/*   Updated: 2024/01/14 17:54:45 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "so_long.h"

void	move_w(t_mlx *m)
{
	void	*img;
	int		w;
	int		h;

	if (m->map[m->p.x][m->p.y] == '1' || m->map[m->p.x][m->p.y] == 'E')
	{
		m->p.y--;
		return ;
	}
	img = mlx_xpm_file_to_image(m->mlx, "./img/Tile.xpm", &w, &h);
	mlx_put_image_to_window(m->mlx, m->win, img, m->p.x * 64, m->p.y * 64 - 64);
	img = mlx_xpm_file_to_image(m->mlx, "./img/HappySheep.xpm", &w, &h);
	mlx_put_image_to_window(m->mlx, m->win, img, m->p.x * 64, m->p.y * 64);
	if (m->map[m->p.x][m->p.y] == 'C' || m->collect > 0)
		m->collect--;
}

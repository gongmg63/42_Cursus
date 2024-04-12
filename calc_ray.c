/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:19:44 by mkong             #+#    #+#             */
/*   Updated: 2024/04/12 18:51:27 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_ray(t_info *info)
{
	t_dda	dda;
	int		i;

	i = 0;
	while (i < WIDTH)
	{
		info->camera_x = 2 * i / (double)WIDTH - 1;
		info->raydir_x = info->dir_x + info->plane_x * info->camera_x;
		info->raydir_y = info->dir_y + info->plane_y * info->camera_x;
		dda.map_x = (int)info->pos_x;
		dda.map_y = (int)info->pos_y;
		dda.deltadist_x = fabs(1 / info->raydir_x);
		dda.deltadist_y = fabs(1 / info->raydir_y);
		dda.hit = 0;
		if (info->raydir_x < 0)
		{
			dda.step_x = -1;
			dda.sidedist_x = (info->pos_x - dda.map_x) * dda.deltadist_x;
		}
		else
		{
			dda.step_x = 1;
			dda.sidedist_x = (dda.map_x + 1.0 - info->pos_x) * dda.deltadist_x;
		}
		if (info->raydir_y < 0)
		{
			dda.step_y = -1;
			dda.sidedist_y = (info->pos_y - dda.map_y) * dda.deltadist_y;
		}
		else
		{
			dda.step_y = 1;
			dda.sidedist_y = (dda.map_y + 1.0 - info->pos_y) * dda.deltadist_y;
		}
		while (!dda.hit)
		{
			if (dda.sidedist_x < dda.sidedist_y)
			{
				dda.sidedist_x += dda.deltadist_x;
				dda.map_x += dda.step_x;
				dda.side = 0;
			}
			else
			{
				dda.sidedist_y += dda.deltadist_y;
				dda.map_y += dda.step_y;
				dda.side = 1;
			}
			if (info->map[dda.map_y][dda.map_x] == '1')
			{
				dda.hit = 1;
				// printf("hit x : %d , hit y : %d, map[x][y] : %c \n", dda.map_x, dda.map_y, info->map[dda.map_y][dda.map_x]);
			}
		}
		if (dda.side == 0)
			dda.perp_wall_dist = (dda.map_x - info->pos_x + (1 - dda.step_x) / 2) / info->raydir_x;
		else
			dda.perp_wall_dist = (dda.map_y - info->pos_y + (1 - dda.step_y) / 2) / info->raydir_y;
		dda.line_height = (int)(HEIGHT / dda.perp_wall_dist);
		dda.draw_start = -dda.line_height / 2 + HEIGHT / 2;
		if (dda.draw_start < 0)
			dda.draw_start = 0;
		dda.draw_end = dda.line_height / 2 + HEIGHT / 2;
		if (dda.draw_end < 0)
			dda.draw_end = HEIGHT - 1;
		draw_verline(*info, dda.draw_start, dda.draw_end, i, 0xFFFF00);
		i += 1;
	}
}

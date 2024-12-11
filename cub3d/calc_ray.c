/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:19:44 by mkong             #+#    #+#             */
/*   Updated: 2024/04/30 17:09:08 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_sidedist(t_info *info, t_dda *dda)
{
	if (info->raydir_x < 0)
	{
		dda->step_x = -1;
		dda->sidedist_x = (info->pos_x - dda->map_x) * dda->deltadist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->sidedist_x = (dda->map_x + 1.0 - info->pos_x) * dda->deltadist_x;
	}
	if (info->raydir_y < 0)
	{
		dda->step_y = -1;
		dda->sidedist_y = (info->pos_y - dda->map_y) * dda->deltadist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->sidedist_y = (dda->map_y + 1.0 - info->pos_y) * dda->deltadist_y;
	}
}

void	get_lay_length(t_info *info, t_dda *dda)
{
	while (!dda->hit)
	{
		if (dda->sidedist_x < dda->sidedist_y)
		{
			dda->sidedist_x += dda->deltadist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->sidedist_y += dda->deltadist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (info->map[dda->map_x][dda->map_y] == '1')
			dda->hit = 1;
	}
}

void	calc_ray(t_info *info)
{
	t_draw_info	d_info;
	t_dda		dda;
	int			i;

	i = 0;
	draw_floor(info, info->f_c_color[0]);
	draw_ceiling(info, info->f_c_color[1]);
	while (i < WIDTH)
	{
		dda = set_dda_info(info, i);
		get_sidedist(info, &dda);
		get_lay_length(info, &dda);
		d_info = set_draw_info(info, &dda);
		draw_texture_line(info, &dda, &d_info, i);
		i++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->data.img, 0, 0);
}

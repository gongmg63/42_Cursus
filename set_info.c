/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:58:29 by mkong             #+#    #+#             */
/*   Updated: 2024/04/30 18:56:20 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture_util(t_info *info, t_map_info *map_info)
{
	int	i;

	i = -1;
	info->texture = (int **)malloc(sizeof(int *) * 4);
	if (info->texture == NULL)
	{
		ft_putendl_fd("Error\nmalloc() failed", 2);
		exit(1);
	}
	while (++i < 4)
	{
		info->texture[i] = (int *)malloc(sizeof(int *) * \
			TEXTURE_WIDTH * TEXTURE_HEIGHT);
		if (info->texture == NULL)
		{
			ft_putendl_fd("Error\nmalloc() failed", 2);
			exit(1);
		}
		ft_memset(info->texture[i], 0, sizeof(int) * \
			TEXTURE_WIDTH * TEXTURE_HEIGHT);
	}
	set_texture_image(info, map_info);
}

void	set_info(t_info *info, t_map_info *map_info)
{
	int	i;

	i = -1;
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "cub3D");
	set_texture_util(info, map_info);
	info->map = copy_map(map_info);
	info->data.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->data.addr = (int *)mlx_get_data_addr(info->data.img, \
					&info->data.bits_per_pixel, \
					&info->data.size_line, &info->data.endian);
	find_start_point(info, map_info);
	set_floor_ceiling_color(info, map_info);
	info->plane_x = (info->dir_y * -1) * 0.67;
	info->plane_y = (info->dir_x * -1) * 0.67;
	info->rotate_speed = 0.02;
	info->move_speed = 0.02;
	free_every_info(map_info);
}

t_draw_info	set_draw_info(t_info *info, t_dda *dda)
{
	t_draw_info	d_info;

	if (dda->side == 0)
		d_info.perp_wall_dist = (dda->map_x - info->pos_x + \
				(1 - dda->step_x) / 2) / info->raydir_x;
	else
		d_info.perp_wall_dist = (dda->map_y - info->pos_y + \
				(1 - dda->step_y) / 2) / info->raydir_y;
	d_info.line_height = (int)(HEIGHT / d_info.perp_wall_dist);
	d_info.draw_start = -d_info.line_height / 2 + HEIGHT / 2;
	if (d_info.draw_start < 0)
		d_info.draw_start = 0;
	d_info.draw_end = d_info.line_height / 2 + HEIGHT / 2;
	if (d_info.draw_end > HEIGHT)
		d_info.draw_end = HEIGHT;
	return (d_info);
}

t_texture_info	set_texture_info(t_info *info, t_dda *dda, t_draw_info *d_info)
{
	t_texture_info	t_info;

	t_info.tex_num = dda->side * 2 + 1;
	if (dda->side == 0 && info->raydir_x < 0)
		t_info.tex_num--;
	else if (dda->side == 1 && info->raydir_y < 0)
		t_info.tex_num--;
	if (dda->side == 0)
		t_info.wall_x = info->pos_y + d_info->perp_wall_dist * info->raydir_y;
	else
		t_info.wall_x = info->pos_x + d_info->perp_wall_dist * info->raydir_x;
	t_info.wall_x -= floor(t_info.wall_x);
	t_info.tex_x = (int)(t_info.wall_x * (double)TEXTURE_WIDTH);
	if ((dda->side == 0 && info->raydir_x > 0) || \
		(dda->side == 1 && info->raydir_y < 0))
		t_info.tex_x = TEXTURE_WIDTH - t_info.tex_x - 1;
	t_info.step = 1.0 * TEXTURE_HEIGHT / d_info->line_height;
	t_info.tex_pos = (d_info->draw_start - HEIGHT / 2 + \
					d_info->line_height / 2) * t_info.step;
	return (t_info);
}

t_dda	set_dda_info(t_info *info, int i)
{
	t_dda	dda;

	info->camera_x = 2 * i / (double)WIDTH - 1;
	info->raydir_x = info->dir_x + info->plane_x * info->camera_x;
	info->raydir_y = info->dir_y + info->plane_y * info->camera_x;
	dda.map_x = (int)info->pos_x;
	dda.map_y = (int)info->pos_y;
	dda.deltadist_x = fabs(1 / info->raydir_x);
	dda.deltadist_y = fabs(1 / info->raydir_y);
	dda.hit = 0;
	return (dda);
}

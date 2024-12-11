/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:10:31 by mkong             #+#    #+#             */
/*   Updated: 2024/04/22 15:20:38 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (char *)data->addr + (y * data->size_line + x * \
			(data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_ceiling(t_info *info, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= HEIGHT / 2)
	{
		j = -1;
		while (++j < WIDTH)
			my_mlx_pixel_put(&info->data, j, i, color);
	}
}

void	draw_floor(t_info *info, int color)
{
	int	i;
	int	j;

	i = HEIGHT;
	while (--i > HEIGHT / 2)
	{
		j = -1;
		while (++j < WIDTH)
			my_mlx_pixel_put(&info->data, j, i, color);
	}	
}

void	draw_texture_line(t_info *info, t_dda *dda, t_draw_info *d_info, int i)
{
	t_texture_info	t_info;

	t_info = set_texture_info(info, dda, d_info);
	while (d_info->draw_start < d_info->draw_end)
	{
		t_info.tex_y = (int)t_info.tex_pos & (TEXTURE_HEIGHT - 1);
		t_info.tex_pos += t_info.step;
		t_info.color = info->texture[t_info.tex_num][TEXTURE_HEIGHT * \
					t_info.tex_y + t_info.tex_x];
		my_mlx_pixel_put(&info->data, i, d_info->draw_start++, t_info.color);
	}
}

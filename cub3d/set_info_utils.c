/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:15:04 by mkong             #+#    #+#             */
/*   Updated: 2024/04/30 18:55:24 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_image(t_info *info, int *texture, char *path, t_data *data)
{
	int	i;
	int	j;
	int	img_width;
	int	img_height;

	data->img = mlx_xpm_file_to_image(info->mlx, path, &img_width, &img_height);
	if (data->img == NULL)
	{
		ft_putendl_fd("Error\nCan't load image", 2);
		exit(1);
	}
	data->addr = (int *)mlx_get_data_addr(data->img, \
			&data->bits_per_pixel, &data->size_line, &data->endian);
	i = -1;
	while (++i < img_height)
	{
		j = -1;
		while (++j < img_width)
			texture[img_width * i + j] = data->addr[img_width * i + j];
	}
	mlx_destroy_image(info->mlx, data->img);
}

void	set_texture_image(t_info *info, t_map_info *map_info)
{
	t_data	data;

	set_image(info, info->texture[0], map_info->texture->north, &data);
	set_image(info, info->texture[1], map_info->texture->south, &data);
	set_image(info, info->texture[2], map_info->texture->west, &data);
	set_image(info, info->texture[3], map_info->texture->east, &data);
}

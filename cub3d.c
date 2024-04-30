/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:18 by mkong             #+#    #+#             */
/*   Updated: 2024/04/30 17:05:32 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_start_point(t_info *info, t_map_info *map_info)
{
	info->pos_x = map_info->map->pos_y + 0.48;
	info->pos_y = map_info->map->pos_x + 0.48;
	if (map_info->map->player_dir == 'N')
	{
		info->dir_x = -1;
		info->dir_y = 0;
	}
	else if (map_info->map->player_dir == 'S')
	{
		info->dir_x = 1;
		info->dir_y = 0;
	}
	else if (map_info->map->player_dir == 'E')
	{
		info->dir_x = 0;
		info->dir_y = 1;
	}
	else if (map_info->map->player_dir == 'W')
	{
		info->dir_x = 0;
		info->dir_y = -1;
	}
}

void	set_floor_ceiling_color(t_info *info, t_map_info *map_info)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		info->f_c_color[0] += map_info->color->floor[i];
		info->f_c_color[1] += map_info->color->ceiling[i];
		if (i != 2)
		{
			info->f_c_color[0] *= 16 * 16;
			info->f_c_color[1] *= 16 * 16;
		}
		i++;
	}
}

char	**copy_map(t_map_info *map_info)
{
	char	**cp_map;
	int		i;

	i = 0;
	cp_map = (char **)malloc(sizeof(char *) * map_info->map->height + 1);
	while (i < map_info->map->height)
	{
		cp_map[i] = ft_strdup(map_info->map->arr[i]);
		i++;
	}
	cp_map[i] = 0;
	return (cp_map);
}

void print_every_info(t_map_info *info)
{
    printf("===== begin printing every info =====\n");
    printf("\n----- print texture -----\n");
    if (info->texture->is_set[0] == 1)
        printf("NORTH: $%s$\n", info->texture->north);
    if (info->texture->is_set[1] == 1)
        printf("SOUTH: $%s$\n", info->texture->south);
    if (info->texture->is_set[2] == 1)
        printf("WEST: $%s$\n", info->texture->west);
    if (info->texture->is_set[3] == 1)
        printf("EAST: $%s$\n", info->texture->east);
    
    printf("\n----- print color -----\n");
    if (info->color->is_set[0] == 1)
        printf("FLOOR: $%d$, $%d$, $%d$\n", info->color->floor[0], info->color->floor[1], info->color->floor[2]);
    if (info->color->is_set[1] == 1)
        printf("CEILING: $%d$, $%d$, $%d$\n", info->color->ceiling[0], info->color->ceiling[1], info->color->ceiling[2]);

    if (info->map->is_set == 1)
    {
        printf("\n----- print info -----\n");
        printf("width: %d\n", info->map->width);
        printf("height: %d\n", info->map->height);
        printf("player_dir: %c\n", info->map->player_dir);
        printf("pos_x: %d\n", info->map->pos_x);
        printf("pos_y: %d\n", info->map->pos_y);

        printf("\n----- print map -----\n");
        for (int i = 0; i < info->map->height; i++)
        {
            printf("%s\n", info->map->arr[i]);
        }
    }
    printf("===== finish printing every info ======\n\n");
}

int	main(int ac, char *av[])
{
	t_map_info	*map_info;
	t_info		info;

	if (ac != 2)
		return (1);
	map_info = parsing(av[1]);
	if (!map_info)
		return (1);
    // print_every_info(map_info); // 값이 잘 할당되었는지 확인용 (추후 삭제하기)
	set_info(&info, map_info);
	calc_ray(&info);
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 0, exit_window, 0);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, key_press, &info);
	mlx_loop(info.mlx);
	return (0);
}

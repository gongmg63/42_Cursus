#include "parsing.h"

void    free_texture(t_texture *texture)
{
    if (texture)
    {
        if (texture->north)
            free(texture->north);
        if (texture->south)
            free(texture->south);
        if (texture->west)
            free(texture->west);
        if (texture->east)
            free(texture->east);
        free(texture);
    }
}

void    free_map(t_map *map)
{
    int i;

    if (map)
    {
        if (map->arr)
        {
            i = 0;
            while (i < map->height)
            {
                if (map->arr[i])
                    free(map->arr[i]);
                i++;
            }
            free(map->arr);
        }
        free(map);
    }
}

void free_every_info(t_map_info *info)
{
    if (info != NULL)
    {
        if (info->texture)
            free_texture(info->texture);
        if (info->color)
            free(info->color);
        if (info->map)
            free_map(info->map);
        free(info);
    }
}

void    free_rgb(char **rgb)
{
    int i;
    
    i = 0;
    if (rgb)
    {
        while (i < 3 && rgb[i] != NULL)
        {
            free(rgb[i]);
            rgb[i] = 0;
            i++;
        }
        free(rgb);
        rgb = 0;
    }
}

int clean_up_map_lst(t_list **map_lst)
{
    ft_lstclear(map_lst, free);
    free(*map_lst);
    *map_lst = NULL;
    return (-1);
}

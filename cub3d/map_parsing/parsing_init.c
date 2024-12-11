#include "parsing.h"

// 이전 코드에서 0으로 초기화하는 부분을 calloc으로 변경
t_map_info *initialize_info(void)
{
    t_map_info	*info;

    info = ft_calloc(1, sizeof(t_map_info));
    if (!info)
        return	(NULL);
    info->texture = ft_calloc(1, sizeof(t_texture));
    info->color = ft_calloc(1, sizeof(t_color));
    info->map = ft_calloc(1, sizeof(t_map));
    if (!info->texture || !info->color || !info->map)
    {
        free_every_info(info);
        return (NULL);
    }
    info->map->pos_x = -1; // -1는 아직 플레이어의 위치가 설정되지 않음을 의미.
    info->map->pos_y = -1;
    return (info);
}

t_list  *initialize_map_lst(void)
{
    t_list  *map_lst;

    map_lst = malloc(sizeof(t_list));
    if (!map_lst)
        return (NULL);
    map_lst->content = NULL;
    map_lst->next = NULL;
    return (map_lst);
}
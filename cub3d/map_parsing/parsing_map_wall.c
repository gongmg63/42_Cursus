#include "parsing.h"

void    get_width_and_height(t_list *map_lst, t_map_info *info)
{
    t_list  *temp;
    int     i;
    int     max_width;

    temp = map_lst->next;
    max_width = 0;
    while (temp)
    {
        i = 0;
        while (((char *)temp->content)[i])
        {
            i++;
        }
        if (i > max_width)
            max_width = i;
        temp = temp->next;
    }
    info->map->width = max_width;
    info->map->height = ft_lstsize(map_lst) - 1;
}

int is_map_surrounded_by_walls(t_list *map_lst, t_map_info *info)
{
    get_width_and_height(map_lst, info);
    info->map->arr = convert_map_lst_to_arr(map_lst, info); // 링크드 리스트로 만들어 놓은 맵을 배열로 변환
    if (info->map->arr == NULL)
    {
        printf("Error: convert_map_lst_to_arr\n");
        return (-1);
    }
    if (is_every_wall_surrounded_by_1(info) == -1)
    {
        printf("Error: wall is not sourrounded by 1\n");
        return (-1);
    }
    return (0);
}
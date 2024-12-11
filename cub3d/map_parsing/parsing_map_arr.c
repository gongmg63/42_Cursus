#include "parsing.h"

char    *allocate_map_row(int width)
{
    char *row;

    row = malloc(sizeof(char) * (width + 1));
    if (!row)
        return (NULL);
    ft_memset(row, ' ', width); // 공백으로 초기화해서 직사각형 모양으로 만듦
    row[width] = '\0';
    return (row);
}

char **allocate_map_array(int height, int width)
{
    char    **map_arr;
    int     i;
    int     j;

    map_arr = malloc(sizeof(char *) * (height + 1));
    if (!map_arr)
        return (NULL);
    i = 0;
    while (i < height)
    {
        map_arr[i] = allocate_map_row(width);
        if (!map_arr[i])
        {
            j = 0;
            while (j < i)
            {
                free(map_arr[j]);
                j++;
            }
            free(map_arr);
            return (NULL);
        }
        i++;
    }
    map_arr[height] = (NULL);
    return (map_arr);
}

void copy_list_to_array(t_list *list, char **array, int width)
{
    int row_idx;
    int col_idx;

    row_idx = 0;
    while (list)
    {
        col_idx = 0;
        while (col_idx < width)
        {
            if (col_idx < (int)ft_strlen(list->content))
                array[row_idx][col_idx] = ((char *)(list->content))[col_idx];
            col_idx++;
        }
        list = list->next;
        row_idx++;
    }
}

/*
링크드 리스트로 만들어 놓은 맵을 배열로 변환
링크드 리스트는 각 줄의 길이가 다른데, 배열로 변환하면서 직사각형으로 만들어줌
*/
char **convert_map_lst_to_arr(t_list *map_lst, t_map_info *info)
{
    char    **map_arr;

    map_arr = allocate_map_array(info->map->height, info->map->width);
    if (!map_arr)
        return (NULL);
    copy_list_to_array(map_lst->next, map_arr, info->map->width);
    return (map_arr);
}

int line_to_map_lst(t_map_info *info, t_list **map_lst, char **line)
{
    if (!is_all_texture_and_color_set(info))
    {
        printf("Error: Not all texture and color are set\n");
        return (-1);
    }
    while (*line)
    {
        if (**line == '\0')
            break;
        ft_lstadd_back(map_lst, ft_lstnew(ft_strdup(*line)));
        free(*line);
        *line = get_next_line(info->fd);
    }
    return (0);
}
#include "parsing.h"

int is_north_closed_by_1(t_map_info *info)
{
    int row_idx;
    int col_idx;

    col_idx = 0;
    while (col_idx < info->map->width)
    {
        row_idx = 0;
        while (row_idx < info->map->height)
        {
            if (info->map->arr[row_idx][col_idx] == '1') // 1이면 벽을 찾았으니까 브레이크
                break;
            else if (info->map->arr[row_idx][col_idx] == ' ') // ' '면 다음 행으로 이동해서 계속 벽 찾기
                row_idx++;
            else
                return (-1);
        }
        col_idx++;
    }
    return (0);
}

int is_south_closed_by_1(t_map_info *info)
{
    int row_idx;
    int col_idx;

    col_idx = 0;
    while (col_idx < info->map->width)
    {
        row_idx = info->map->height - 1;
        while (row_idx >= 0)
        {
            if (info->map->arr[row_idx][col_idx] == '1')
                break;
            else if (info->map->arr[row_idx][col_idx] == ' ')
                row_idx--;
            else
                return (-1);
        }
        col_idx++;
    }
    return (0);
}

int is_east_closed_by_1(t_map_info *info)
{
    int row_idx;
    int col_idx;

    row_idx = 0;
    while (info->map->arr[row_idx])
    {
        col_idx = info->map->width - 1;
        while (col_idx >= 0)
        {
            if (info->map->arr[row_idx][col_idx] == '1')
                break;
            else if (info->map->arr[row_idx][col_idx] == ' ')
                col_idx--;
            else
                return (-1);
        }
        row_idx++;
    }
    return (0);
}

int is_west_closed_by_1(t_map_info *info)
{
    int row_idx;
    int col_idx;

    row_idx = 0;
    while (info->map->arr[row_idx])
    {
        col_idx = 0;
        while (info->map->arr[row_idx][col_idx])
        {
            if (info->map->arr[row_idx][col_idx] == '1')
                break;
            else if (info->map->arr[row_idx][col_idx] == ' ')
                col_idx++;
            else
                return (-1);
        }
        row_idx++;
    }
    return (0);
}

// 동서남북이 모두 1로 닫혀있는지 확인
int is_every_wall_surrounded_by_1(t_map_info *info)
{
    if (is_north_closed_by_1(info) == -1)
    {
        printf("Error: North is not closed by 1\n");
        return (-1);
    }
    if (is_south_closed_by_1(info) == -1)
    {
        printf("Error: South is not closed by 1\n");
        return (-1);
    }
    if (is_east_closed_by_1(info) == -1)
    {
        printf("Error: East is not closed by 1\n");
        return (-1);
    }
    if (is_west_closed_by_1(info) == -1)
    {
        printf("Error: West is not closed by 1\n");
        return (-1);
    }
    return (0);
}
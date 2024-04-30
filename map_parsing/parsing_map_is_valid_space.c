#include "parsing.h"

// 플레이어의 바로 옆이 1이거나 공백이어야 함
int check_right(t_map_info *info, int row, int col)
{
    if (info->map->arr[row][col + 1] && \
        info->map->arr[row][col + 1] != '1' && \
        info->map->arr[row][col + 1] != ' ')
        {
            printf("Error: Invalid right space at (%d, %d)\n", row, col + 1);
            return (-1);
        }
    return (0);
}

// 플레이어의 바로 옆이 1이거나 공백이어야 함
int check_left(t_map_info *info, int row, int col)
{
    if (col > 0 && \
        info->map->arr[row][col - 1] != '1' && \
        info->map->arr[row][col - 1] != ' ')
        {
            printf("Error: Invalid left space at (%d, %d)\n", row, col - 1);
            return (-1);
        }
    return (0);
}

int check_up(t_map_info *info, int row, int col)
{
    if (row > 0 && \
        info->map->arr[row - 1][col] != '1' && \
        info->map->arr[row - 1][col] != ' ')
        {
            printf("Error: Invalid up space at (%d, %d)\n", row - 1, col);
            return (-1);
        }
    return (0);
}

int check_down(t_map_info *info, int row, int col)
{
    if (info->map->arr[row + 1] && \
        info->map->arr[row + 1][col] != '1' && \
        info->map->arr[row + 1][col] != ' ')
        {
            printf("Error: Invalid down space at (%d, %d)\n", row + 1, col);
            return (-1);
        }
    return (0);
}

/*
is_map_surrounded_by_wall() 함수만으로는 맵이 유효한지 확인할 수 없다.
따라서 is_valid_space() 함수로 맵의 공백이 유효한지 확인함.
공백의 오른쪽, 왼쪽, 위, 아래가 모두 1이거나 공백이어야 함.
4방향을 모두 확인해서 플레이어가 이동할 수 있는 공간인지 확인함.

유효하면 0 리턴,
그렇지 않으면 에러 메시지 출력 후 -1 리턴
*/

// 주석 지우면 25줄 이내로 줄어듦
int is_valid_space(t_map_info *info)
{
    int row_idx;
    int col_idx;

    row_idx = 0;
    while (info->map->arr[row_idx])
    {
        col_idx = 0;
        while (info->map->arr[row_idx][col_idx])
        {
            if (info->map->arr[row_idx][col_idx] == ' ')
            {
                if (check_right(info, row_idx, col_idx) == -1 || \
                    check_left(info, row_idx, col_idx) == -1 || \
                    check_up(info, row_idx, col_idx) == -1 || \
                    check_down(info, row_idx, col_idx) == -1)
                    {
                        printf("Error: Invalid space at (%d, %d)\n", row_idx, col_idx);
                        return -1;
                    }
            }
            col_idx++;
        }
        row_idx++;
    }
    info->map->is_set = 1;
    return (0);
}

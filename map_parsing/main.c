#include "parsing.h"

// 값이 잘 할당되었는지 확인용 (추후 삭제하기)
// void print_every_info(t_map_info *info)
// {
//     printf("===== begin printing every info =====\n");
//     printf("\n----- print texture -----\n");
//     if (info->texture->is_set[0] == 1)
//         printf("NORTH: $%s$\n", info->texture->north);
//     if (info->texture->is_set[1] == 1)
//         printf("SOUTH: $%s$\n", info->texture->south);
//     if (info->texture->is_set[2] == 1)
//         printf("WEST: $%s$\n", info->texture->west);
//     if (info->texture->is_set[3] == 1)
//         printf("EAST: $%s$\n", info->texture->east);
    
//     printf("\n----- print color -----\n");
//     if (info->color->is_set[0] == 1)
//         printf("FLOOR: $%d$, $%d$, $%d$\n", info->color->floor[0], info->color->floor[1], info->color->floor[2]);
//     if (info->color->is_set[1] == 1)
//         printf("CEILING: $%d$, $%d$, $%d$\n", info->color->ceiling[0], info->color->ceiling[1], info->color->ceiling[2]);

//     if (info->map->is_set == 1)
//     {
//         printf("\n----- print info -----\n");
//         printf("width: %d\n", info->map->width);
//         printf("height: %d\n", info->map->height);
//         printf("player_dir: %c\n", info->map->player_dir);
//         printf("pos_x: %d\n", info->map->pos_x);
//         printf("pos_y: %d\n", info->map->pos_y);

//         printf("\n----- print map -----\n");
//         for (int i = 0; i < info->map->height; i++)
//         {
//             printf("%s\n", info->map->arr[i]);
//         }
//     }
//     printf("===== finish printing every info ======\n\n");
// }

void leak()
{
    system("leaks cub3D");
}

// int main(int ac, char **av)
// {
//     atexit(leak);
//     t_map_info  *info;
//     char    *cube_file;

//     if (ac != 2)
//         return (1);
//     cube_file = av[1];
//     info = parsing(cube_file);
//     if (!info)
//         return (1);
//     print_every_info(info); // 값이 잘 할당되었는지 확인용 (추후 삭제하기)
//     free_every_info(info);
//     return (0);
// }

// TODO: 요소 중 1개라도 설정되지 않은 경우 에러 처리하기

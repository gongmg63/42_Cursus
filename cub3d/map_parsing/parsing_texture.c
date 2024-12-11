#include "parsing.h"

int assign_texture_based_on_type(t_map_info *info, char *trimmed_path, t_prefix_type type)
{
    if (type == NORTH)
        info->texture->north = trimmed_path;
    else if (type == SOUTH)
        info->texture->south = trimmed_path;
    else if (type == WEST)
        info->texture->west = trimmed_path;
    else if (type == EAST)
        info->texture->east = trimmed_path;
    else
    {
        free(trimmed_path);
        return (-1);
    }
    return (0);
}

// 프린트에프 삭제하면 25줄 안으로 줄어듬
int set_texture(t_map_info *info, char *line, t_prefix_type type)
{
    char    *path;
    char    *trimmed_path;
    int     result;

    if (info->texture->is_set[type] == 1)
    {
        printf("Error: %s texture is already set\n", line);
        return (-1);
    }
    path = ft_strtrim(line, " ");
    if (!path)
    {
        printf("Error: ft_strtrim() failed\n");
        return (-1);
    }
    trimmed_path = ft_strtrim(path + 3, " ");  // path + 3 해서 "NO " 이런식으로 띄어쓰기 뒤에 path가 나오게 함
    free(path);
    if (!trimmed_path || *trimmed_path == '\0' || open(trimmed_path, O_RDONLY) == -1)
    {
        printf("Error: Invalid texture path or cannot open the path\n");
        free(trimmed_path);
        return (-1);
    }
    result = assign_texture_based_on_type(info, trimmed_path, type);
    if (result == -1)
        return (-1);
    info->texture->is_set[type] = 1;
    return 0;
}

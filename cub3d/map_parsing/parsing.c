#include "parsing.h"

// int validate_and_open_file(char *filename)
// {
//     int     fd;
//     char    *extention;

//     extention = ft_strrchr(filename, '.');
//     if (!extention)
//     {
//         write(1, "Invalid file extention!", 23);
//         return (-1);
//     }
//     if (ft_strncmp(extention, ".cub", 4) != 0 || extention[4] != '\0')
//     {
//         write(1, "Invalid file extention!", 23);
//         return (-1);
//     }
//     fd = open(filename, O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (-1);
//     }
//     return (fd);
// }

int parse_line(t_map_info **info, char **line_ptr)
{
    t_prefix_type   type;

    type = get_prefix_type(*line_ptr);
    if (type == NORTH || type == SOUTH || type == WEST || type == EAST)
    {
        if (set_texture(*info, *line_ptr, type) == -1)
            return (-1);
    }
    else if (type == FLOOR || type == CEILING)
    {
        if (set_color(*info, *line_ptr, type) == -1)
            return (-1);
    }
    else if (type == MAP)
    {
        if (set_map(*info, line_ptr) == -1) {
            return (-1);
        }
    }
    else
    {
        printf("Error: Invalid line\n");
        return (-1);
    }
    return (0);
}

int is_every_element_set(t_map_info *info)
{
    int is_every_texture_set;
    int is_every_color_set;
    int is_map_set;

    is_every_texture_set = 0;
    is_every_color_set = 0;
    is_map_set = 0;
    is_every_texture_set = info->texture->is_set[0] && info->texture->is_set[1] \
    && info->texture->is_set[2] && info->texture->is_set[3];
    is_every_color_set = info->color->is_set[0] && info->color->is_set[1];
    is_map_set = info->map->is_set;
    if (!is_every_texture_set || !is_every_color_set || !is_map_set)
    {
        printf("not every element is set \n");
        return (-1);
    }
    return (0);
}

t_map_info *parsing(char *cube_file)
{
    t_map_info          *info;
    char            *line;
    int            result;

    info = initialize_info();
    info->fd = validate_and_open_file(cube_file);
    if (info->fd == -1)
    {
        free_every_info(info);
        return (NULL);
    }
    while ((line = get_next_line(info->fd)) != NULL)
    {
        if (*line == '\0' || *line == '\n' || is_line_only_spaces(line))
        {
            free(line);
            continue;
        }
        result = parse_line(&info, &line);
        free(line);
        if (result == -1)
        {
            free_every_info(info);
            close(info->fd);
            return (NULL);
        }
    }
    close(info->fd);
    if (is_every_element_set(info) == -1)
    {
        printf("Error: Not every element is set\n");
        close(info->fd);
        return (NULL);
    }
    return (info);
}
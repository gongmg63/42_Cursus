#include "parsing.h"

// 출력해서 확인용 (나중에 삭제)
void print_map_lst(t_list *map_lst)
{
	t_list *curr;

	curr = map_lst->next;
	while (curr)
	{
		printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}
}

int is_all_texture_and_color_set(t_map_info *info)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (info->texture->is_set[i] == 0)
            return (0);
        i++;
    }
    i = 0;
    while (i < 2)
    {
        if (info->color->is_set[i] == 0)
            return (0);
        i++;
    }
    return (1);
}

void assign_start_position_values(t_map_info *info, int x, int y, char news)
{
    info->map->pos_x = x;
    info->map->pos_y = y;
    info->map->player_dir = news;
}

int check_line_for_news(t_map_info *info, char *line, int y)
{
    int x;
    
    x = 0;
    while (line[x])
    {
        if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E' || line[x] == 'W')
        {
            if (info->map->is_news_set == 1)
                return (-1);
            assign_start_position_values(info, x, y, line[x]);
            info->map->is_news_set = 1;
        }
        x++;
    }
    return (0);
}

int is_only_one_news(t_list *map_lst, t_map_info *info)
{
    t_list  *temp;
    int     y;
    int     result;
    
    y = 0;
    temp = map_lst->next;
    while (temp)
    {
        result = check_line_for_news(info, (char *)temp->content, y);
        if (result == -1)
        {
            printf("Error: Multiple player positions found\n");
            return (-1);
        }
        y++;
        temp = temp->next;
    }
    if (info->map->is_news_set == 0)
    {
        printf("Error: No player position found\n");
        return (-1);
    }
    return (0);
}

int set_map(t_map_info *info, char **line_ptr)
{
    t_list *map_lst;

    map_lst = initialize_map_lst();
    if (map_lst == NULL)
        return -1;
    if (line_to_map_lst(info, &map_lst, line_ptr) == -1 || \
        is_only_one_news(map_lst, info) == -1 || \
        is_map_composed_of_valid_characters(map_lst) == -1 || \
        is_map_surrounded_by_walls(map_lst, info) == -1 || \
        is_valid_space(info) == -1)
        {
            printf("Error: invalid map\n");
            return clean_up_map_lst(&map_lst);
        }
    // print_map_lst(map_lst); // 확인용 (삭제하기)
    ft_lstclear(&map_lst, free);
    free(map_lst);
    return (0);
}

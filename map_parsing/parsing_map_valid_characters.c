#include "parsing.h"

int is_string_valid(char *str)
{
    int i;

    str = ft_strtrim(str, " ");
    i = 0;
    while (str[i])
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != 'N' &&
            str[i] != 'S' && str[i] != 'E' && str[i] != 'W' &&
            str[i] != ' ')
        {
            printf("Error: Invalid character in map\n");
            free(str);
            return (-1);
        }
        i++;
    }
    free(str);
    return (0);
}


int is_map_composed_of_valid_characters(t_list *map_lst)
{
    t_list *temp;
    
    temp = map_lst->next;
    while (temp)
    {
        if (is_string_valid(temp->content) == -1)
        {
            return (-1);
        }
        temp = temp->next;
    }
    return (0);
}

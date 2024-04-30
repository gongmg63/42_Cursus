#include "parsing.h"

int ft_isspace(int c)
{
    if (c == ' ' || c == '\t' || c == '\n' ||
        c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

int	is_line_only_spaces(char *str)
{
    while (*str != '\0')
    { 
        if (!ft_isspace(*str))
        {
            return (0);
        }
        str++;
    }
    return (1);
}


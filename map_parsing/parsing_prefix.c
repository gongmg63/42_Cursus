#include "parsing.h"

t_prefix_type get_prefix_type(char *line)
{
    char			*trimmed_line;
	t_prefix_type	type;

    trimmed_line = ft_strtrim(line, " \t\n\v\f\r");
    if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
        type = NORTH;
    else if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
        type = SOUTH;
    else if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
        type = WEST;
    else if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
        type = EAST;
    else if (ft_strncmp(trimmed_line, "F ", 2) == 0)
        type = FLOOR;
    else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
        type = CEILING;
    else if (ft_strncmp(trimmed_line, "1", 1) == 0)
        type = MAP;
    else
        type = NONE;
    free(trimmed_line);
    return (type);
}

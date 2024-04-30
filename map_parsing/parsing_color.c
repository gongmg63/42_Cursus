#include "parsing.h"

char	**trim_rgb_spaces(char **rgb)
{
    int		i;
    char	**rgb_trimmed;

    rgb_trimmed = (char **)malloc(sizeof(char *) * 3);
    if (!rgb_trimmed)
    {
        printf("Error: malloc() failed\n");
        return (NULL);
    }
	i = 0;
	while (i < 3)
    {
        rgb_trimmed[i] = ft_strtrim(rgb[i], " ");
        if (!rgb_trimmed[i])
        {
            printf("Error: ft_strtrim() failed\n");
            return (NULL);
        }
		i++;
    }
    return (rgb_trimmed);
}

void assign_color(t_map_info *info, t_prefix_type type, char **trimmed_rgb)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (type == FLOOR)
			info->color->floor[i] = ft_atoi(trimmed_rgb[i]);
		else if (type == CEILING)
			info->color->ceiling[i] = ft_atoi(trimmed_rgb[i]);
		i++;
	}
	info->color->is_set[type - FLOOR] = 1; // 0: floor, 1: ceiling 중 하나가 설정되었음을 표시
}

char **parse_and_validate_color(char *line)
{
    char	*color;
	char	**rgb;

	color = ft_strtrim(line + 2, " ");
    if (!color || count_comma(color) != 2)
	{
        free(color);
        return (NULL);
    }
    rgb = ft_split(color, ',');
    free(color);
    if (!is_valid_rgb(rgb))
	{
        free_rgb(rgb);
        return (NULL);
    }
    return (rgb);
}

int set_color(t_map_info *info, char *line, t_prefix_type type)
{
	char	**rgb;
	char	**trimmed_rgb;

	if (info->color->is_set[type - FLOOR] == 1)
		return (-1);
	rgb = parse_and_validate_color(line);
	if (!rgb)
		return (-1);
	if (!is_valid_rgb(rgb))
		return (-1);
	trimmed_rgb = trim_rgb_spaces(rgb);
	if (!trimmed_rgb)
	{
		free_rgb(rgb);
		return (-1);
	}
	assign_color(info, type, trimmed_rgb);
	free_rgb(trimmed_rgb);
	free_rgb(rgb);
	return (0);
}

#include "parsing.h"

int count_comma(char *str)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == ',')
			count++;
		str++;
	}
	return (count);
}

int is_digit(char *str)
{
	while (*str)
	{
		if (*str == ' ')
		{
			str++;
			continue;
		}
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	is_valid_rgb(char **rgb)
{
    int i;
    int value;

	// rgb 3개 값이 유효한지 확인
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
    {
        free_rgb(rgb);
        return (0);
    }
	// 0~255 사이의 값인지 확인
	i = 0;
	while (i < 3)
    {
        value = ft_atoi(rgb[i]);
        if (value < 0 || value > 255 || !is_digit(rgb[i]))
        {
			ft_putendl_fd("Error\nRGB value must be between 0 and 255", 2);
            free_rgb(rgb);
            return (0);
        }
		i++;
    }
    return (1);
}

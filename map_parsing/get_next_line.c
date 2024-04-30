#include "parsing.h"

int	get_nl_or_eof_idx(char *str)
{
	int idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '\n')
			return (idx);
		idx++;
	}
	return (idx);
}

char	*get_remaining_buffer(char *buf)
{
	char	*new_buf;
	int		i;
	int		j;

	i = get_nl_or_eof_idx(buf);

	if (buf[i] == '\0')
	{
		free(buf);
		return (NULL);
	}
	new_buf = ft_calloc(ft_strlen(buf) - i + 1, sizeof(char));
	i++;
	j = 0;
	while (buf[i + j])
	{
		new_buf[j] = buf[i + j];
		j++;
	}
	free(buf);
	return (new_buf);
}

char	*extract_line_from_buffer(char *buf)
{
	char	*line;
	int		i;
	int		idx_nl;

	if (*buf == '\0')
		return (NULL);
	idx_nl = get_nl_or_eof_idx(buf);
	line = ft_calloc(idx_nl + 2, sizeof(char));
	i = 0;
	while (i < idx_nl)
	{
		line[i] = buf[i];
		i++;
	}
	return (line);
}

char *read_until_newline(int fd, char *res)
{
	int		bytes_read;
	char	*temp;
	char	*prev_buf;

	if (!res)
		res = ft_calloc(1, sizeof(char));
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(res);
			free(temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		prev_buf = res;
		res = ft_strjoin(res, temp);
		free(prev_buf);
		if (ft_strchr(res, '\n'))
			break;
	}
	free(temp);
	return (res);
}

char *get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0)
		return (NULL);
	buf = read_until_newline(fd, buf);
	if (!buf)
		return (NULL);
	line = extract_line_from_buffer(buf);

	buf = get_remaining_buffer(buf);
	return (line);
}
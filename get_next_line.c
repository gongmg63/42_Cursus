/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:47 by mkong             #+#    #+#             */
/*   Updated: 2023/11/17 21:28:49 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strnjoin(char *s1, char const *s2, size_t n)
{
	char	*result;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	result = (char *)malloc(sizeof(char) * (s1_len + n + 1));
	if (result == 0)
		return (0);
	*result = '\0';
	ft_strlcat(result, s1, s1_len + 1);
	ft_strlcat(result, s2, s1_len + n + 1);
	free(s1);
	return (result);
}

static void	exist_nl(char *r_str, char *str)
{
	r_str = ft_strndup(str, check_nl(str));
	str = deln_buf(str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*r_str;
	char		*buf;
	ssize_t		r_bytes;

	r_bytes = BUFFER_SIZE;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == 0)
		return (0);
	if (str == 0)
	{
		r_bytes = read(fd, buf, BUFFER_SIZE);
		buf[r_bytes] = 0;
		str = ft_strndup(buf, r_bytes);
	}
	if (check_nl(str))
		exist_nl(r_str, str);
	else
	{
		r_str = ft_strndup(str, ft_strlen(str));
		while (r_bytes == BUFFER_SIZE && !check_nl(str))
		{
			r_bytes = read(fd, buf, BUFFER_SIZE);
			buf[r_bytes] = 0;
			if (r_bytes != 0)
				str = ft_strndup(buf, r_bytes);
			if (check_nl(str))
			{
				r_str = ft_strnjoin(r_str, str, check_nl(str));
				str = deln_buf(str);
			}
			else
				r_str = ft_strnjoin(r_str, str, r_bytes);
		}
	}
	free(buf);
	return (r_str);
}

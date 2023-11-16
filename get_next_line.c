/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:47 by mkong             #+#    #+#             */
/*   Updated: 2023/11/16 17:00:25 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

static size_t	check_newline(const char *str)
{
	size_t	cnt;

	cnt = 0;
	while (*str && *str != '\n')
	{
		cnt++;
		str++;
	}
	return (cnt);
}

static char	*ft_strndup(const char *s1, size_t n)
{
	char	*arr;
	int		idx;

	arr = (char *)malloc(sizeof(char) * (n + 1));
	if (arr == 0)
		return (0);
	while (n != 0)
	{
		arr[idx] = s1[idx];
		idx++;
		n--;
	}
	arr[idx] = '\0';
	return (arr);
}

static size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;

	len_src = check_newline(src);
	if (dst == 0 && dstsize == 0)
		return (len_src);
	len_dst = check_newline(dst);
	dst += len_dst;
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	while (dstsize - 1 > len_dst && *src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	*dst = '\0';
	return (len_dst + len_src);
}

static char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*result;
	size_t	s1_len;

	s1_len = check_newline(s1);
	result = (char *)malloc(sizeof(char) * (s1_len + n + 1));
	if (result == 0)
		return (0);
	*result = '\0';
	ft_strlcat(result, s1, s1_len + 1);
	ft_strlcat(result, s2, s1_len + n + 1);
	return (result);
}

char	*get_next_line(int fd)
{
	static size_t	idx;
	static char		*buf;
	char			*str;
	size_t			l_len;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == 0)
		return (0);
	read(fd, buf, BUFFER_SIZE);
	buf[BUFFER_SIZE] = 0;
	l_len = check_newline(buf);
	if (buf[idx + l_len] == '\n')
		str = ft_strndup(buf + idx, l_len + 1);
	else
	{
		str = ft_strndup(buf + idx, l_len);
		while (buf[idx + l_len] != '\n' && (l_len + idx == BUFFER_SIZE))
		{
			idx = 0;
			read(fd, buf, BUFFER_SIZE);
			l_len = check_newline(buf);
			str = ft_strnjoin(str, buf, l_len + 1);
		}
	}
	idx += l_len + 1;
	free(buf);
	return (str);
}

static int	check_nl(char *buf)
{
	int	cnt;

	cnt = 1;
	while (*buf)
	{
		if (*buf == '\n')
			return (cnt);
		buf++;
		cnt++;
	}
	return (0);
}

static size_t	ft_strlen(char *s)
{
	size_t	length;

	length = 0;
	while (*s)
	{
		s++;
		length++;
	}
	return (length);
}

static char	*deln_buf(char *buf)
{
	char	*str;
	size_t	st_idx;

	st_idx = check_nl(buf) + 1;
	if (buf[st_idx])
	{
		str = ft_strndup(buf + st_idx, ft_strlen(buf + st_idx));
		if (str == 0)
			return (0);
	}
	else
		str = 0;
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*str;
	ssize_t		r_bytes;

	if (buf == 0)
	{
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == 0)
			return (0);
		read(fd, buf, BUFFER_SIZE);
	}
	if (!check_nl(buf))
	{
		str = ft_strndup(buf, check_nl(buf));
		buf = deln_buf(buf);
	}
	else
	{
		
	}
}

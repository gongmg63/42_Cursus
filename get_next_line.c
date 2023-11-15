/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:47 by mkong             #+#    #+#             */
/*   Updated: 2023/11/15 21:55:04 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 1024

static size_t	check_newline(char *str)
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

static char	*ft_strdup(const char *s1)
{
	size_t	s1_len;
	char	*arr;

	s1_len = check_newline(s1);
	arr = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (arr == 0)
		return (0);
	while (*s1 && *s1 != '\n')
	{
		*arr = *s1;
		arr++;
		s1++;
	}
	*arr = '\0';
	return (arr - s1_len);
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

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = check_newline(s1);
	s2_len = check_newline(s2);
	result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == 0)
		return (0);
	*result = '\0';
	ft_strlcat(result, s1, s1_len + 1);
	ft_strlcat(result, s2, s1_len + s2_len + 1);
	return (result);
}

char	*get_next_line(int fd)
{
	static size_t	idx;
	char			*buf;
	char			*str;
	size_t			l_len;	

	idx = 0;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == 0)
		return (0);
	read(fd, buf, BUFFER_SIZE);
	l_len = check_newline(buf);
	if (buf[idx + l_len] == '\n')
		str = ft_strdup(buf + idx);
	else
	{
		str = ft_strdup(buf + idx);
		while (buf[idx + l_len] != '\n')
		{
			idx = 0;
			read(fd, buf, BUFFER_SIZE);
			l_len = check_newline(buf);
			str = ft_strjoin(str, buf);
		}
		str = ft_strjoin(str, "\n");
	}
}

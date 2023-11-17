/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:47 by mkong             #+#    #+#             */
/*   Updated: 2023/11/17 18:46:29 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

#include <stdio.h>

static size_t	check_newline(const char *str)
{
	size_t	cnt;

	cnt = 0;
	while (*str && *str != '\n')
	{
		cnt++;
		str++;
	}
	if (*str == '\n')
		cnt++;
	return (cnt);
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

static char	*ft_strndup(const char *s1, size_t n)
{
	char	*arr;
	int		idx;

	idx = 0;
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

static size_t	check_nl(char *buf)
{
	size_t	cnt;

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

static char	*deln_buf(char *buf)
{
	char	*str;
	size_t	st_idx;

	st_idx = check_nl(buf);
	str = ft_strndup(buf + st_idx, BUFFER_SIZE - st_idx);
	if (str == 0)
		return (0);
	free(buf);
	return (str);
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
	{
		r_str = ft_strndup(str, check_nl(str));
		str = deln_buf(str);
	}
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

#include <fcntl.h>


int main()
{
	int		fd = open("abc", O_RDONLY);
	char	*a;

	a = get_next_line(fd);
	printf("main : %s \n", a);
	a = get_next_line(fd);
	printf("main 2 : %s \n", a);
	a = get_next_line(fd);
	printf("main 3 : %s \n", a);
}

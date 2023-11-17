/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:52 by mkong             #+#    #+#             */
/*   Updated: 2023/11/17 21:21:57 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	check_nl(char *buf)
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

size_t	ft_strlen(const char *s)
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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (dst == 0 && dstsize == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
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

char	*deln_buf(char *buf)
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

char	*ft_strndup(const char *s1, size_t n)
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

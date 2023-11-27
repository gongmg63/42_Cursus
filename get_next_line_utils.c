/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:52 by mkong             #+#    #+#             */
/*   Updated: 2023/11/27 20:34:57 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	check_nl(char *buf)
{
	size_t	cnt;

	if (buf == 0)
		return (0);
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

char	*ft_strnjoin(char *s1, char const *s2, size_t n)
{
	char	*result;
	size_t	s1_len;
	size_t	idx;

	idx = 0 - 1;
	if (n == 0)
		return (s1);
	s1_len = ft_strlen(s1);
	result = (char *)malloc(s1_len + n + 1);
	if (result == 0)
	{
		free(s1);
		return (0);
	}
	while (++idx < s1_len)
		result[idx] = s1[idx];
	while (n-- > 0)
	{
		result[idx] = s2[idx - s1_len];
		idx++;
	}
	result[idx] = 0;
	free(s1);
	return (result);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*arr;
	int		idx;

	idx = 0;
	if (n == 0)
		return (0);
	arr = (char *)malloc(n + 1);
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
